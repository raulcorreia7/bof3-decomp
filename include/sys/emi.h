#ifndef SYSTEM_EMI_H
#define SYSTEM_EMI_H

#include "types.h"

/* The EMI container: a sector-aligned archive with a header, a 16-byte TOC row
 * per entry, and one payload per entry. A TOC row's type says what the payload
 * is (a RAM copy, a packed payload, a graphics upload, a VAB header or body, a cue
 * table, a sequence package) and its load argument is a destination or a
 * selector for that type. The main executable's loader copies or maps each
 * payload. Evidence: all 880 US Breath of Fire III (USA) archives and the loader readers;
 * @source: wiki:formats/emi. */

/* Container layout, measured over all 880 US Breath of Fire III (USA) archives (@source: wiki:formats/emi#padding). */
#define EMI_SECTOR_SIZE             0x800 /* payload alignment; also the first payload offset */
#define EMI_STREAM_TIMEOUT_FRAMES   301   /* frames without progress before a read restarts */
#define EMI_DATA_OFFSET             0x800u
#define EMI_MAGIC_OFFSET            0x08 /* archive header magic offset, before the TOC at 0x10 */
#define EMI_MAGIC_SIZE              8    /* archive header magic size; see EMI_MAGIC_STR */
#define EMI_MAGIC_STR               "MATH_TBL"
#define EMI_ARCHIVE_HEADER_SIZE     0x10
#define EMI_TOC_ENTRY_SIZE          0x10   /* TOC row size; the header is 0x10 + entry_count * 0x10 bytes */
#define EMI_TOC_ENTRY_PAD           0x2e2e /* fill of the TOC entry u16 at 0x0e */
#define EMI_HEADER_FILL             0x2e   /* fill from the TOC end up to EMI_SECTOR_SIZE */
#define EMI_PAYLOAD_FILL            0x5f   /* fill from a payload end to the next EMI_SECTOR_SIZE boundary */

/* Entry slots inside one archive, by archive kind (disc names; @source: wiki:formats/emi). The bank
 * selectors are the load_arg of the VAB entries. BENEMY, BGM and the first BPLCHAR bank hold a VAB
 * triple at slots 0-2. */
#define EMI_BENEMY_SLOT_VAB_HEADER  0
#define EMI_BENEMY_SLOT_CUES        1
#define EMI_BENEMY_SLOT_VAB_BODY    2
#define EMI_BENEMY_BANK             6

#define EMI_BGM_SLOT_VAB_HEADER     0
#define EMI_BGM_SLOT_SEQUENCE       1
#define EMI_BGM_SLOT_VAB_BODY       2 /* 3 when the archive also carries a cue table at 2 */
#define EMI_BGM_BANK                0

/* A whole bank holds three VAB triples around a zero filler and the LZ77 container;
 * a one-section bank holds the first triple and one section. */
#define EMI_BPLCHAR_SLOT_VAB_HEADER 0
#define EMI_BPLCHAR_SLOT_CUES       1
#define EMI_BPLCHAR_SLOT_VAB_BODY   2
#define EMI_BPLCHAR_SLOT_SECTION    3 /* one-section bank */
#define EMI_BPLCHAR_SLOT_FILLER     3 /* whole bank */
#define EMI_BPLCHAR_SLOT_CONTAINER  7 /* whole bank */
#define EMI_BPLCHAR_BANK_FIRST      3
#define EMI_BPLCHAR_BANK_SECOND     4
#define EMI_BPLCHAR_BANK_THIRD      5

#define EMI_PLCHAR_SLOT_VAB_HEADER  0
#define EMI_PLCHAR_SLOT_CUES        1
#define EMI_PLCHAR_SLOT_VAB_BODY    2
#define EMI_PLCHAR_SLOT_CONTAINER   3 /* PLxxx: the character bank, LZ77 */
#define EMI_PLCHAR_SLOT_PROGRAM     0 /* PLPxxx: the character program */
#define EMI_PLCHAR_BANK             1

/* Entry type ids (@source: wiki:formats/emi#entry-types): what the loader does with a payload.
 * EMILoaderState holds the two internal loader states. */
typedef enum EMIEntryType {
    EMI_ENTRY_COPY          = 0,  /* RAM payload copied to load_arg; may hold code or data */
    EMI_ENTRY_PACKED        = 1,  /* LZ77 payload (include/sys/lz77.h) decoded to load_arg */
    EMI_ENTRY_QUEUED        = 2,  /* queued for the streaming ring with type 1 (EMI_LoadCompressed) */
    EMI_ENTRY_GRAPHICS      = 3,  /* raw graphics upload; load_arg is the upload descriptor */
    EMI_ENTRY_VAB_HEADER    = 6,  /* VAB header; load_arg is the bank selector */
    EMI_ENTRY_VAB_BODY      = 7,  /* VAB body of the same bank */
    EMI_ENTRY_CUES          = 8,  /* one VAB bank's cue table
                                   * (@source: wiki:formats/audio#emi-type-8-cue-records) */
    EMI_ENTRY_SEQUENCE_COPY = 9,  /* sequence-side copy with type 10 (EMI_LoadSequence) */
    EMI_ENTRY_SEQUENCE      = 10, /* SEP sequence package (include/audio/sep.h) */
} EMIEntryType;

/* The leading word of every loaded module payload: the id the type-0 loader
 * compares with the archive TOC's cached first word (@source: wiki:formats/emi). The
 * ids are unique per body and line up with the archive families: etc
 * 0x12-0x20 plus 0x141, scenario 0x105-0x11D, boss 0x11E-0x140, battle-effect
 * 0x142-0x143, battle-effect module (bmagic) 0x144-0x1BF. A copy payload keeps
 * its source's id. */
typedef u32 EMIModuleId;

/* States the loader keeps in the type cell besides the entry types. EMI_NextEntry sets
 * EMI_LOADER_STATE_ARCHIVE_HEADER while it reads the archive's first sector; EMI_ReadToc
 * handles it. */
typedef enum EMILoaderState {
    EMI_LOADER_STATE_ARCHIVE_HEADER = 5,
} EMILoaderState;

/* Never executable: EMI is a sector-aligned data container, so an entry is classified by type alone
 * (@source: wiki:formats/emi#entry-types). */
typedef struct EMIArchiveHeader {
    u32 entry_count;           /* 0x00 */
    u32 version;               /* 0x04; 1 in all 880 US Breath of Fire III (USA) archives */
    u8  magic[EMI_MAGIC_SIZE]; /* 0x08; EMI_MAGIC_STR */
} EMIArchiveHeader;

ASSERT_SIZE(EMIArchiveHeader, EMI_ARCHIVE_HEADER_SIZE);

/* TOC rows start at 0x10, one per entry, and each payload starts on an EMI_SECTOR_SIZE
 * boundary: `next = current + ((size + 0x7ff) & ~0x7ff)`. `load_arg` is not always a CPU
 * pointer - it is a destination or a selector per type (@source: wiki:formats/emi#load-argument). */
typedef struct EMITocEntry {
    u32 size;       /* 0x00 payload byte size */
    u32 load_arg;   /* 0x04 type-dependent load argument */
    u32 first_word; /* 0x08 cached first payload word */
    u16 type;       /* 0x0c EMIEntryType id */
    u16 padding;    /* 0x0e EMI_TOC_ENTRY_PAD */
} EMITocEntry;

ASSERT_SIZE(EMITocEntry, EMI_TOC_ENTRY_SIZE);

#endif
