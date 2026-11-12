#ifndef BMAGIC_DRAW_SPARKLE_RAYS_H
#define BMAGIC_DRAW_SPARKLE_RAYS_H

/* Draws the rays of the sparkle at WORK as four LINE_G2 segments fanning out from the effect position: the angle
 * advances 8 per ray over a 0x20 span and each ray is queued at the effect cell with the shade the effect timer
 * (byte 0x05) sets. */
/* func_801EF810 (magic070, magic071, magic072), func_801EFBF8 (magic073), func_801EFBE4 (magic074), func_801EF80C
   (magic162, magic168) */

/* The sparkle ray scratch: the effect position at 0 and 1, the ray angle at 3 and its shade at 4 to 6. */
extern u16 D_1F800000_HALF[];

#define BMAGIC_DRAW_SPARKLE_RAYS(WORK, ANGLE, RADIUS)                                                 \
    LINE_G2* prim;                                                                                    \
    s32      i;                                                                                       \
                                                                                                      \
    D_1F800000_HALF[0] = (WORK)->unk_20;                                                              \
    D_1F800000_HALF[1] = (WORK)->unk_22;                                                              \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);                        \
    Area_AddCellPrim((WORK)->pos.x.fixed, (WORK)->pos.y.fixed, 2, sizeof(DR_MODE));                   \
    D_1F800000_HALF[4] = (WORK)->timer_05 * 6;                                                        \
    D_1F800000_HALF[5] = (WORK)->timer_05 * 6;                                                        \
    D_1F800000_HALF[6] = (WORK)->timer_05 * 6;                                                        \
    for (i = (ANGLE); i < (ANGLE) + 0x20; i += 8) {                                                   \
        prim = (LINE_G2*)g_GfxPrimCursor;                                                             \
        SetLineG2(prim);                                                                              \
        SetSemiTrans(prim, 1);                                                                        \
        D_1F800000_HALF[3] = (i & 0x1F) << 7;                                                         \
        prim->x0           = D_1F800000_HALF[0];                                                      \
        prim->y0           = D_1F800000_HALF[1];                                                      \
        prim->x1           = D_1F800000_HALF[0] + ((rcos((s16)D_1F800000_HALF[3]) * (RADIUS)) >> 12); \
        prim->y1           = D_1F800000_HALF[1] + ((rsin((s16)D_1F800000_HALF[3]) * (RADIUS)) >> 12); \
        setRGB0(prim, D_1F800000_HALF[4], D_1F800000_HALF[5], D_1F800000_HALF[6]);                    \
        setRGB1(prim, 1, 1, 1);                                                                       \
        Area_AddCellPrim((WORK)->pos.x.fixed, (WORK)->pos.y.fixed, 2, 32);                            \
    }

/* Draws the long rays of the sparkle at WORK as four LINE_G3 segments from the effect position through a half-radius
 * shade point to the full radius, the angle advancing 8 per ray over a 0x20 span, and queues each at the effect cell. */
/* func_801EFA44 (magic070, magic071, magic072), func_801EFE2C (magic073), func_801EFE18 (magic074), func_801EFA40
   (magic162, magic168) */
#define BMAGIC_DRAW_SPARKLE_LONG_RAYS(WORK, ANGLE, RADIUS)                                                   \
    LINE_G3* prim;                                                                                           \
    s32      i;                                                                                              \
                                                                                                             \
    D_1F800000_HALF[0] = (WORK)->unk_20;                                                                     \
    D_1F800000_HALF[1] = (WORK)->unk_22;                                                                     \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);                               \
    Area_AddCellPrim((WORK)->pos.x.fixed, (WORK)->pos.y.fixed, 2, sizeof(DR_MODE));                          \
    D_1F800000_HALF[4] = (WORK)->timer_05 * 6;                                                               \
    D_1F800000_HALF[5] = (WORK)->timer_05 * 6;                                                               \
    D_1F800000_HALF[6] = (WORK)->timer_05 * 6;                                                               \
    for (i = (ANGLE); i < (ANGLE) + 0x20; i += 8) {                                                          \
        prim = (LINE_G3*)g_GfxPrimCursor;                                                                    \
        SetLineG3(prim);                                                                                     \
        SetSemiTrans(prim, 1);                                                                               \
        D_1F800000_HALF[3] = (i & 0x1F) << 7;                                                                \
        prim->x0           = D_1F800000_HALF[0];                                                             \
        prim->y0           = D_1F800000_HALF[1];                                                             \
        prim->x1           = D_1F800000_HALF[0] + ((rcos((s16)D_1F800000_HALF[3]) * ((RADIUS) >> 1)) >> 12); \
        prim->y1           = D_1F800000_HALF[1] + ((rsin((s16)D_1F800000_HALF[3]) * ((RADIUS) >> 1)) >> 12); \
        prim->x2           = D_1F800000_HALF[0] + ((rcos((s16)D_1F800000_HALF[3]) * (RADIUS)) >> 12);        \
        prim->y2           = D_1F800000_HALF[1] + ((rsin((s16)D_1F800000_HALF[3]) * (RADIUS)) >> 12);        \
        setRGB0(prim, 1, 1, 1);                                                                              \
        setRGB1(prim, D_1F800000_HALF[4], D_1F800000_HALF[5], D_1F800000_HALF[6]);                           \
        setRGB2(prim, 1, 1, 1);                                                                              \
        Area_AddCellPrim((WORK)->pos.x.fixed, (WORK)->pos.y.fixed, 2, 32);                                   \
    }

#endif
