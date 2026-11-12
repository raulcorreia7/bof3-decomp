#ifndef BMAGIC_DRAW_SPARKLE_LONG_RAYS_H
#define BMAGIC_DRAW_SPARKLE_LONG_RAYS_H

/* Draws the long rays of the sparkle at WORK as four LINE_G3 segments from the effect position through a half-radius
 * shade point to the full radius, the angle advancing 8 per ray over a 0x20 span, and queues each at the effect cell. */
/* func_801EFA44 (magic070, magic071, magic072), func_801EFE2C (magic073), func_801EFE18 (magic074), func_801EFA40
   (magic162, magic168) */
#define BMAGIC_DRAW_SPARKLE_LONG_RAYS(WORK, ANGLE, RADIUS)                                                               \
    LINE_G3* prim;                                                                                                       \
    s32      i;                                                                                                          \
                                                                                                                         \
    D_1F800000.view.ray.x = (WORK)->unk_20;                                                                              \
    D_1F800000.view.ray.y = (WORK)->unk_22;                                                                              \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);                                           \
    Area_AddCellPrim((WORK)->pos.x.fixed, (WORK)->pos.y.fixed, 2, sizeof(DR_MODE));                                      \
    D_1F800000.view.ray.red   = (WORK)->timer_05 * 6;                                                                    \
    D_1F800000.view.ray.green = (WORK)->timer_05 * 6;                                                                    \
    D_1F800000.view.ray.blue  = (WORK)->timer_05 * 6;                                                                    \
    for (i = (ANGLE); i < (ANGLE) + 0x20; i += 8) {                                                                      \
        prim = (LINE_G3*)g_GfxPrimCursor;                                                                                \
        SetLineG3(prim);                                                                                                 \
        SetSemiTrans(prim, 1);                                                                                           \
        D_1F800000.view.ray.angle = (i & 0x1F) << 7;                                                                     \
        prim->x0                  = D_1F800000.view.ray.x;                                                               \
        prim->y0                  = D_1F800000.view.ray.y;                                                               \
        prim->x1                  = D_1F800000.view.ray.x + ((rcos(D_1F800000.view.ray.angle) * ((RADIUS) >> 1)) >> 12); \
        prim->y1                  = D_1F800000.view.ray.y + ((rsin(D_1F800000.view.ray.angle) * ((RADIUS) >> 1)) >> 12); \
        prim->x2                  = D_1F800000.view.ray.x + ((rcos(D_1F800000.view.ray.angle) * (RADIUS)) >> 12);        \
        prim->y2                  = D_1F800000.view.ray.y + ((rsin(D_1F800000.view.ray.angle) * (RADIUS)) >> 12);        \
        setRGB0(prim, 1, 1, 1);                                                                                          \
        setRGB1(prim, D_1F800000.view.ray.red, D_1F800000.view.ray.green, D_1F800000.view.ray.blue);                     \
        setRGB2(prim, 1, 1, 1);                                                                                          \
        Area_AddCellPrim((WORK)->pos.x.fixed, (WORK)->pos.y.fixed, 2, 32);                                               \
    }

#endif
