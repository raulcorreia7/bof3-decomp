#include "engine/slus/slus.h"

/* Draws one sprite of a scene record as an FT4 primitive: projects the record origin, skips it when it falls outside
 * the screen margin, picks an animation frame from g_FrameCount modulo the frame count and sizes the quad from the
 * frame's byte offsets, scaled by the projected depth.
 */
MATCH void Area_DrawSceneSprite(u8* record, s32 origin_x, s32 origin_y) {
    POLY_FT4* prim;
    u8*       frame;
    s32       z;
    s32       i;
    s32       n;
    s32       x;
    s32       y;
    long      depth;
    long      flag;

    if ((Area_TestCondition(FIELD(s16, record, 0x0)) << 24) == 0) {
        return;
    }
    D_1F800014->vx = ((origin_x - 0x80) << 0x7) + FIELD(s8, record, 7) * 2;
    D_1F800014->vy = ((origin_y - 0x80) << 7) + FIELD(s8, record, 0x6) * 2;
    D_1F800014->vz = FIELD(s32, record, 0x4);
    /* FAKE: retail reads D_1F800034 as u16[]. */
    z              = RotTransPers(D_1F800014, (long*)((u16*)D_1F800034), &depth, &flag);
    if (((u32)(((u16*)D_1F800034)[0] + 0x3C) & HALF_MASK) >= 0x1B9) {
        return;
    }
    /* FAKE: retail reads D_1F800034 as u16[]. */
    if (((u32)(((u16*)D_1F800034)[1] + 0x96) & HALF_MASK) >= 0x1C3) {
        return;
    }
    i = 0;
    if (z == 0) {
        return;
    }
    n = g_FrameCount % record[8];
    while (1) {
        if (n < record[0xA + i]) {
            break;
        }
        i++;
    }
    prim = (POLY_FT4*)g_GfxPrimCursor;
    n    = (u32)(record[9] + 5) >> 2;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    /* FAKE: integer address arithmetic keeps the retail add order and reuses the index register. */
    frame    = (u8*)((i << 3) + ((n << 2) + (s32)record));
    /* FAKE: retail reads D_1F800034 as u16[]. */
    x        = ((u16*)D_1F800034)[0] - FIELD(s8, frame, 0x8) * 1125 / z;
    prim->x0 = prim->x2 = x;
    x += (s8)(FIELD(u32, frame, 0x8) >> 8) * 1125 / z;
    prim->x1 = prim->x3 = x;
    /* FAKE: retail reads D_1F800034 as u16[]. */
    y                   = ((u16*)D_1F800034)[1] - FIELD(s8, frame, 0xA) * 1125 / z;
    prim->y0 = prim->y1 = y;
    y += FIELD(s8, frame, 0xB) * 1125 / z;
    prim->y2 = prim->y3 = y;
    func_80155560(FIELD(u32, frame, 0xC), prim, 1);
    GFX_AddPrim((FIELD(u32, frame, 0xC) & 0x40000000) ? 6 : g_AreaDrawMode, sizeof(POLY_FT4));
}
