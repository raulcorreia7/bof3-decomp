#ifndef OVERLAY_GAME_00_SHARED_H
#define OVERLAY_GAME_00_SHARED_H

/* SLUS_004.22 words the game overlay reads. They live in their own header
 * because the scene-matrix unit cannot include the full image header:
 * slus/area.h declares its own Camera_SetMatrix with a caller-only
 * void return. */

#endif
