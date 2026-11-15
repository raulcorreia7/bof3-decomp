#ifndef AUDIO_BGM_H
#define AUDIO_BGM_H

#include "types.h"

#define BGM_TRACK_COUNT       165

#define BGM_TRACK_SIZE        0x04

/* Selection ids and the SND_PlayBGM arguments the screens share. The ids are
 * named for the screen that starts them; the retail track names are unknown. */
#define BGM_NONE              0xFF /* g_SndBGMId while no track is active */
#define BGM_TITLE             0x8D /* Game_BeginTitle */
#define BGM_COMMU02           0x94 /* the commu02 overlay's own track */
#define BGM_CUE_LEVEL_DEFAULT 100
#define BGM_CUE_SHAPE_DEFAULT 8

/* One row of the selection table at 0x80181EB8, indexed by the selection id
 * (g_SndBGMId). SND_RequestBGM compares bank_slot with the active
 * row and starts that archive through EMI_LoadArchive; the music
 * archives sit at EMI_SLOT_BGM and up. The selection effects read sep_slot as
 * the index into the SEP package table g_SelectionEffectVoices and sequence as the sequence
 * number inside that package (SND_StartDecrescendo, SsSepReplay). */
typedef struct BGMTrack {
    u16 bank_slot; /* 0x00 loader slot id of the music archive */
    u8  sep_slot;  /* 0x02 SEP package index, g_SelectionCues */
    u8  sequence;  /* 0x03 sequence number in the package, g_SelectionSequences */
} BGMTrack;

ASSERT_SIZE(BGMTrack, BGM_TRACK_SIZE);
ASSERT_OFFSET(BGMTrack, sep_slot, 0x02);
ASSERT_OFFSET(BGMTrack, sequence, 0x03);

#endif
