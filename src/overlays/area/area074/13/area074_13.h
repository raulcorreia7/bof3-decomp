#ifndef OVERLAY_WORLD01_AREA074_13_H
#define OVERLAY_WORLD01_AREA074_13_H

/* The world01/area074/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"
#include "area/spad.h"

extern u32 D_80144F94;

/* FAKE: the cue dispatcher takes the id as a word; the slus prototype narrows it to u16,
 * and the caller here adds 0x100 to a halfword before the call. */
#define SND_PLAY_SE_ID ((void (*)(s32))SND_PlaySE)

#endif
