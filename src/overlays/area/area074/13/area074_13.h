#ifndef OVERLAY_WORLD01_AREA074_13_H
#define OVERLAY_WORLD01_AREA074_13_H

/* The world01/area074/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

/* The master's verdict on the party's fighting style. */
#define AREA074_MSG_MASTER_ACCEPTS  0x92
#define AREA074_MSG_MASTER_REFUSES  0x93
#define AREA074_MSG_MASTER_FAREWELL 0x94

extern u32 D_80144F94;

/* FAKE: the cue dispatcher takes the id as a word; the slus prototype narrows it to u16,
 * and the caller here adds 0x100 to a halfword before the call. */
#define SND_PLAY_CUE_ID ((void (*)(s32))SND_PlayCue)

#endif
