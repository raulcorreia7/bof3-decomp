#ifndef AUDIO_SE_H
#define AUDIO_SE_H

/* One VAB bank's sound-effect table from an EMI type-8 entry: 4-byte
 * records naming an SPU voice, a VAB program and a tone. The dispatcher
 * `SND_SEPlay` (`0x8015DF18`) splits an SE id into bank and record index, then
 * calls that bank's reader through `g_SndSeReaders[bank]`; the reader keys the
 * record's voices.
 *
 * @source: wiki:formats/audio#emi-type-8-cue-records derives this layout
 * from the seven readers (`0x8015E994`-`0x80160E38`) and all 8,608 records in
 * the 904 disc entries. A bitfield's allocation is the compiler's, so the bytes
 * stay plain members and the masks below extract the fields.
 *
 * Layout: 31 records in the chunk at `0x801486A0 + 124 * bank`, banks 0-6.
 * A disc entry holds at most 24 records and a payload size that is a multiple
 * of 4 (904/904 entries). The VAB tone tables the readers index with the
 * record's program and tone live with the executable's data in slus/slus.h. */

#include "types.h"

#define EMI_SE_RECORD_SIZE  0x04

/* The field masks the seven bank readers apply to an SE record. */
#define EMI_SE_ALIAS_MASK   0x07
#define EMI_SE_PROGRAM_MASK 0x7F
#define EMI_SE_COMPARE_MASK 0x0F
#define EMI_SE_VOICE_MASK   0x1F
#define EMI_SE_LAYER_MASK   0x60

/* The sound banks, by what each holds. */
typedef enum SndBank {
    SND_BANK_BGM    = 0,
    SND_BANK_COMMON = 1,
    SND_BANK_AREA   = 2,
    SND_BANK_ENEMY  = 6,
} SndBank;

/* The SE id: bank in bits 8-11, record index in bits 0-7. */
#define EMI_SE_ID_BANK_SHIFT   8
#define EMI_SE_ID_BANK_MASK    0x0F00
#define EMI_SE_ID_INDEX_MASK   0x00FF

#define EMI_SE_ID_BANK(id)     (((id) & EMI_SE_ID_BANK_MASK) >> EMI_SE_ID_BANK_SHIFT)
#define EMI_SE_ID_INDEX(id)    ((id) & EMI_SE_ID_INDEX_MASK)

/* SE id: `(bank << 8) | record_index`. The images call the dispatcher with
 * the constructed id, e.g. `emi/etc/game/00@0x8019B024` passes bank 1,
 * record 6. */
#define EMI_SE_ID(bank, index) ((((u32)(bank) << EMI_SE_ID_BANK_SHIFT) & EMI_SE_ID_BANK_MASK) | ((u32)(index) & EMI_SE_ID_INDEX_MASK))

typedef struct EMISE {
    u8 alias_bank; /* bits 2-0: bank that supplies the voice index and its VAB
                    * volume, pan and tune; 0 = own bank. 0 in all 8,608 entries;
                    * bits 7-3 are zero in all of them, role unknown. */
    u8 program;    /* EMISEProgramFlags; bit 7 EMI_SE_USE_VOLUME_FLAG: set follows the key-on with
                    * SsUtSetDetVVol(voice, SE volL, SE volR); clear keeps the
                    * tone's own volume. Bits 6-0: tone block 0-7, the third
                    * SsUtKeyOnV argument. */
    u8 tone;       /* bits 7-4: tone slot 0-14, the fourth SsUtKeyOnV argument.
                    * Bits 3-0 are copied to voice state and compared with the
                    * previous SE's value (the retrigger decision): 0x10 in
                    * 8,342 entries, 0x11 in 239, other values in 27. Role
                    * unknown. */
    u8 voice;      /* bits 4-0: first SPU voice 0-23. Bits 6-5: layers, extra
                    * voices keyed on the SE (0 in 525 entries, 1 in 7,662, 2 in
                    * 248, 3 in 173). Bit 7 is zero in all 8,608 entries, role
                    * unknown. */
} EMISE;

ASSERT_SIZE(EMISE, EMI_SE_RECORD_SIZE);

typedef enum EMISEProgramFlags {
    EMI_SE_USE_VOLUME_FLAG = 1 << 7,
} EMISEProgramFlags;

#endif
