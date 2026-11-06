#ifndef AUDIO_BGM_H
#define AUDIO_BGM_H

#include "types.h"

#define BGM_TRACK_COUNT 165

#define BGM_TRACK_SIZE  0x04

/* One row of the selection table at 0x80181EB8, indexed by the selection id
 * (g_SndBGMId). SND_RequestBGM compares bank_slot with the active
 * row and starts that archive through EMI_LoaderStreamInitSlot; the music
 * archives sit at EMI_SLOT_BGM and up. The selection effects read sep_slot as
 * the index into the SEP package table g_SelectionFxVoices and sequence as the sequence
 * number inside that package (SND_StartDecrescendo, SsSepReplay). */
typedef struct BGMTrack {
    u16 bank_slot; /* 0x00 loader slot id of the music archive */
    u8  sep_slot;  /* 0x02 SEP package index, g_SelectionCues */
    u8  sequence;  /* 0x03 sequence number in the package, D_80181EBB */
} BGMTrack;

ASSERT_SIZE(BGMTrack, BGM_TRACK_SIZE);
ASSERT_OFFSET(BGMTrack, sep_slot, 0x02);
ASSERT_OFFSET(BGMTrack, sequence, 0x03);

#endif
