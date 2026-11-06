#ifndef MENU_SAVE_H
#define MENU_SAVE_H

#include "types.h"

/*
 * Save-image frame and its checksum.
 *
 * The record frame is the RAM image of a save file: `&g_Zenny - 0x878`, so
 * the notes' `+0x878` zenny is frame-relative. The card driver proves the frame
 * by writing the "SC" magic into it, and START.EMI's checksum routine
 * (0x801E5A00) closes the loop by treating `frame + 0x8E8` as the play clock,
 * which is exactly g_PlayClock at 0x80144FC0.
 *
 * Checksum: zero the halfword at `frame + 0x270`, sum
 * `SAVE_CHECKSUM_LENGTH` bytes from `frame + 0x200` in a 32-bit accumulator,
 * and compare the low halfword against the stored value.
 */

#define SAVE_FRAME           0x801446D8u

/* The persistent block at D_801448D8 that boot zeroes, the save copies to its payload at frame + 0x200 and the
 * checksum covers whole: 4,272 bytes. */
#define SAVE_CHECKSUM_FIRST  0x200u
#define SAVE_BLOCK_SIZE      0x10B0u
#define SAVE_CHECKSUM_LENGTH SAVE_BLOCK_SIZE
/* The file the card calls open and transfer on: the payload ends at 0x12B0 (frame + 0x200 + 0x10B0). */
#define SAVE_CHECKSUM_SLOT   0x270u
#define SAVE_FILE_SIZE       0x12B0
#define SAVE_CHECKSUM_MASK   0xFFFFu

/* Frame-relative fields from @source: wiki:data/records#save-layout. */
#define SAVE_ZENNY           0x878
#define SAVE_WALKING_ORDER   0x880
#define SAVE_FORMATION_FLAGS 0x881
#define SAVE_BATTLE_ORDER    0x883
#define SAVE_CLOCK           0x8E8
#define SAVE_FISHING_RECORD  0x90C
#define SAVE_DRAGON_GENES    0xE70
#define SAVE_CELERITY_TIMER  0xE7C
#define SAVE_BONEBREAK_TIMER 0xE80
#define SAVE_NAME            0xEA0
#define SAVE_PORTRAITS       0xEA5
#define SAVE_LEVEL           0xEA8
#define SAVE_TIMER           0xEAC
#define SAVE_FAIRY_JOB       0xEF0

#endif
