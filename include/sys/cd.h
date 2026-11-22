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
