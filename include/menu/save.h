#ifndef MENU_SAVE_H
#define MENU_SAVE_H

#include "types.h"
#include "menu/save_data.h"

/* Save-image frame and its checksum. */

#define SAVE_FRAME           0x801446D8u

#define SAVE_CHECKSUM_FIRST  0x200u
#define SAVE_CHECKSUM_LENGTH SAVE_BLOCK_SIZE
/* The file the card calls open and transfer on: the payload ends at 0x12B0 (frame + 0x200 + 0x10B0). */
#define SAVE_FILE_SIZE       0x12B0
#define SAVE_CHECKSUM_SLOT   0x270u
#define SAVE_CHECKSUM_MASK   0xFFFFu

/* Frame-relative fields from @source: wiki:data/records#save-layout. */
#define SAVE_ZENNY           0x878
#define SAVE_FORMATION       0x880
#define SAVE_FORMATION_FLAGS 0x881
#define SAVE_FIELD_ORDER     0x882
#define SAVE_BATTLE_ORDER    0x885
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

/* The frame offsets agree with SaveData, which the frame holds from SAVE_CHECKSUM_FIRST on. */
STATIC_ASSERT(save_frame_checksum, DECOMP_OFFSETOF(SaveData, checksum) + SAVE_CHECKSUM_FIRST == SAVE_CHECKSUM_SLOT);
STATIC_ASSERT(save_frame_zenny, DECOMP_OFFSETOF(SaveData, zenny) + SAVE_CHECKSUM_FIRST == SAVE_ZENNY);
STATIC_ASSERT(save_frame_party_formation,
              DECOMP_OFFSETOF(SaveData, party_formation) + SAVE_CHECKSUM_FIRST == SAVE_FORMATION);
STATIC_ASSERT(save_frame_field_order, DECOMP_OFFSETOF(SaveData, field_order) + SAVE_CHECKSUM_FIRST == SAVE_FIELD_ORDER);
STATIC_ASSERT(save_frame_battle_order,
              DECOMP_OFFSETOF(SaveData, battle_order) + SAVE_CHECKSUM_FIRST == SAVE_BATTLE_ORDER);
STATIC_ASSERT(save_frame_play_clock, DECOMP_OFFSETOF(SaveData, play_clock) + SAVE_CHECKSUM_FIRST == SAVE_CLOCK);
STATIC_ASSERT(save_frame_fish_best_catch,
              DECOMP_OFFSETOF(SaveData, fish_best_catch) + SAVE_CHECKSUM_FIRST == SAVE_FISHING_RECORD);
STATIC_ASSERT(save_frame_celerity_timer,
              DECOMP_OFFSETOF(SaveData, celerity_timer) + SAVE_CHECKSUM_FIRST == SAVE_CELERITY_TIMER);
STATIC_ASSERT(save_frame_bonebreak_timer,
              DECOMP_OFFSETOF(SaveData, bonebreak_timer) + SAVE_CHECKSUM_FIRST == SAVE_BONEBREAK_TIMER);
STATIC_ASSERT(save_frame_fairy_jobs, DECOMP_OFFSETOF(SaveData, fairy_jobs) + SAVE_CHECKSUM_FIRST == SAVE_FAIRY_JOB);
STATIC_ASSERT(save_frame_block, sizeof(SaveData) == SAVE_BLOCK_SIZE);

#endif
