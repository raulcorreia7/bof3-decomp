#ifndef OVERLAY_GAME_00_SHARED_H
#define OVERLAY_GAME_00_SHARED_H

#include "work/area_spad.h"

/* SLUS_004.22 words the game overlay reads. They live in their own header
 * because the scene-matrix unit cannot include the full image header:
 * slus/functions.h declares its own Area_SetCameraMatrix with a caller-only
 * void return. */
extern u8 D_80145FCC[];

#endif
