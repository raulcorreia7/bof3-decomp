#ifndef OVERLAY_WORLD03_AREA128_13_H
#define OVERLAY_WORLD03_AREA128_13_H

/* The world03/area128/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"
#include "scenario/state.h"
#include "area/spad.h"

/* One point of the glow ring: its position and the grey level of the ring edge there. */
typedef struct AreaGlowPoint {
    s16 x;
    s16 y;
    s16 z;
    u8  shade;
    u8  unk_07;
} AreaGlowPoint;

/* How far out the glow reaches from a point, and the height it reaches there. */
typedef struct AreaGlowReach {
    s16 radius;
    s16 z;
} AreaGlowReach;

extern AreaGlowPoint D_801F32E0[];
extern AreaGlowReach D_801F3328[];
/* The glow quads func_801F2C04 draws. */
#define AREA128_GLOW_QUAD_COUNT 6
/* The first point of each glow quad: the quad spans it and the next one. */
extern u8 D_801F334C[AREA128_GLOW_QUAD_COUNT];

#endif
