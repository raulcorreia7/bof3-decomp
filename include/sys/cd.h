#ifndef SYSTEM_CD_H
#define SYSTEM_CD_H

#include "cd_format.h"
#include "sys/emi.h"
#include "types.h"

/* The main executable's CD and EMI loader runtime: the per-entry loader
 * records, the transfer state, and the step counter that advances one entry.
 * The disc file list layout it reads (DiscLba, the slot ids and the family
 * bases) is the format header cd_format.h. */

/* retail addresses */

/* Both callback initialization and cursor wrap use 24 slots (EMI_LdrStreamInitSlot, EMI_LdrServiceStream). */
#define EMI_CALLBACK_SLOT_COUNT 24

/* The CD loader state CD_Update dispatches on; g_CdStateHandlers holds the handler of each state. */
typedef enum CdState {
    CD_STATE_IDLE       = 0, /* CD_Idle */
    CD_STATE_SET_SPEED  = 1, /* CD_SetSpeed */
    CD_STATE_SEEK       = 2, /* CD_Seek */
    CD_STATE_SEEK_WAIT  = 3, /* CD_OnSeek */
    CD_STATE_READ       = 4, /* CD_Read */
    CD_STATE_READ_WAIT  = 5, /* CD_OnRead */
    CD_STATE_PAUSE      = 6, /* CD_Pause */
    CD_STATE_PAUSE_WAIT = 7, /* CD_OnPause */
    CD_STATE_IDLE_END   = 8, /* CD_Idle, the stream's last state */
} CdState;

#define CD_STATE_COUNT  9

/* The loader's step counter, a word in the bank mapped at 0x80140000 (EMI_LdrLoadVabBody, EMI_LdrLoadVabCues,
 * EMI_LdrLoadSequence). */
#define EMI_LOADER_STEP (*(volatile u32*)(D_80140000 + 0x646C))

/* The load in flight: the disc sector it reads from, then its TOC row with `size` counting down. */
typedef struct EMIActiveLoad {
    u32         active_lba;
    EMITocEntry entry;
} EMIActiveLoad;

ASSERT_OFFSET(EMIActiveLoad, entry, 0x04);
ASSERT_SIZE(EMIActiveLoad, 0x14);

/* The CD/EMI stream: the entry being transferred, its ring cursor, the CD callback state and the
 * last sync result. The individual g_Emi* and g_Cd* globals are access views of its members. */
typedef struct EMIStream {
    /* 0x00 */ volatile u32 start_sector;
    /* 0x04 */ volatile u32 bytes_left;
    /* 0x08 */ volatile u32 load_arg;
    /* 0x0C */ volatile u32 first_word;
    /* 0x10 */ volatile u16 entry_type;
    /* 0x12 */ u16          pad_12;
    /* 0x14 */ volatile u32 ring_base;
    /* 0x18 */ volatile u32 requested_slot;
    /* 0x1C */ u32          step;
    /* 0x20 */ s32          upload_bytes_left; /* g_EmiUploadBytesLeft */
    /* 0x24 */ volatile u32 upload_cursor;     /* D_80146478 */
    /* 0x28 */ u8           pad_28[0x08];
    /* 0x30 */ volatile u8  read_status;
    /* 0x31 */ volatile u8  next_slot;
    /* 0x32 */ u8           upload_bank;
    /* 0x33 */ u8           entry_bank;
    /* 0x34 */ volatile u8  vab_slot;     /* D_80146484 */
    /* 0x35 */ volatile u8  source_index; /* D_80146485 */
    /* 0x36 */ volatile u8  unk_36;       /* D_80146486 */
    /* 0x37 */ u8           pad_37;
    /* 0x38 */ s8           ring_index; /* g_EmiRingIndex */
    /* 0x39 */ s8           ring_slot;
    /* 0x3A */ s8           cd_state; /* CdState */
    /* 0x3B */ s8           unk_3B;   /* D_8014648B: bit flags and the pre-start state */
    /* 0x3C */ s32          cd_sync_status;
    /* 0x40 */ u16          idle_frames;
    /* 0x42 */ u16          seek_retries; /* g_EmiSeekRetries */
    /* 0x44 */ u8           state;
    /* 0x45 */ u8           pad_45[0x03];
    /* 0x48 */ u8           sync_result[8]; /* g_EmiSyncResult */
} EMIStream;

ASSERT_OFFSET(EMIStream, start_sector, 0x00);
ASSERT_OFFSET(EMIStream, bytes_left, 0x04);
ASSERT_OFFSET(EMIStream, load_arg, 0x08);
ASSERT_OFFSET(EMIStream, first_word, 0x0C);
ASSERT_OFFSET(EMIStream, entry_type, 0x10);
ASSERT_OFFSET(EMIStream, ring_base, 0x14);
ASSERT_OFFSET(EMIStream, requested_slot, 0x18);
ASSERT_OFFSET(EMIStream, step, 0x1C);
ASSERT_OFFSET(EMIStream, upload_bytes_left, 0x20);
ASSERT_OFFSET(EMIStream, upload_cursor, 0x24);
ASSERT_OFFSET(EMIStream, read_status, 0x30);
ASSERT_OFFSET(EMIStream, next_slot, 0x31);
ASSERT_OFFSET(EMIStream, upload_bank, 0x32);
ASSERT_OFFSET(EMIStream, entry_bank, 0x33);
ASSERT_OFFSET(EMIStream, vab_slot, 0x34);
ASSERT_OFFSET(EMIStream, source_index, 0x35);
ASSERT_OFFSET(EMIStream, ring_index, 0x38);
ASSERT_OFFSET(EMIStream, ring_slot, 0x39);
ASSERT_OFFSET(EMIStream, cd_state, 0x3A);
ASSERT_OFFSET(EMIStream, cd_sync_status, 0x3C);
ASSERT_OFFSET(EMIStream, idle_frames, 0x40);
ASSERT_OFFSET(EMIStream, seek_retries, 0x42);
ASSERT_OFFSET(EMIStream, state, 0x44);
ASSERT_OFFSET(EMIStream, sync_result, 0x48);
ASSERT_SIZE(EMIStream, 0x50);

/* D_80146450 */
extern EMIStream g_EmiStream;

/* The EXE-side stream entry points are registry rows (EMI_Ldr*). */

/* D_80146468 */
extern volatile u32 g_EmiRequestedSlotId;

/* Disc/read-side helpers. */
/* Loads the archive of the requested BGM selection when it differs from the active one, then starts its cue. */
/* EXE-side stream entry points. */
/* Starts the key-based CD request for one XA stream file; the key is the file type in bits 12 and up and an
 * entry count below. Every caller also passes a second word that the loader never reads. */
/* Arms the loader for a character's family key (three party bytes plus the form flag) and waits for the stream. */

#endif
