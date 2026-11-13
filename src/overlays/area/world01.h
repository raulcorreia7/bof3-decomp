#ifndef WORLD01_FAMILY_H
#define WORLD01_FAMILY_H

#include "sys/gameui.h"
#include "overlays/area/area.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT       0xFF

/* The shop panel step the request sets. */
#define g_MenuMasterSubStep      (*(s8*)&g_MenuMasterSubStep)

/* Draws the ring of eight Gouraud triangles around (x, y) at the radius, one per angle step, its
 * colour row read from the three channel symbols. A bare statement macro, not `do { } while (0)`:
 * the wrapper steers register allocation. Each member declares `prim` and `i`; every change must
 * verify func_801F30C0 and func_801F3274. */
#define AREA_DRAW_TRIANGLE_FAN(x, y, radius, angle, red, green, blue)                                \
    i = 0;                                                                                           \
    do {                                                                                             \
        prim     = GFX_BeginPolyG3(1);                                                               \
        prim->x0 = x;                                                                                \
        prim->y0 = y;                                                                                \
        prim->x1 = x + FIXED_MUL(radius, rcos(angle));                                               \
        prim->y1 = y + FIXED_MUL(radius, rsin(angle));                                               \
        angle += AREA_RING_ANGLE_STEP;                                                               \
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));                                               \
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));                                               \
        /* The row's unk_06 selects one colour triplet of the table. */                              \
        setRGB0(prim, red[g_Task->unk_06 * 3], green[g_Task->unk_06 * 3], blue[g_Task->unk_06 * 3]); \
        setRGB1(prim, 0, 0, 0);                                                                      \
        setRGB2(prim, 0, 0, 0);                                                                      \
        i += 1;                                                                                      \
        GFX_AddPrim(3, sizeof(POLY_G3));                                                             \
    } while (i < 8)

#endif
