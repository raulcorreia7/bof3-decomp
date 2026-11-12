#ifndef BMAGIC_EFFECT_DRAW_SPARKLE_RAYS_H
#define BMAGIC_EFFECT_DRAW_SPARKLE_RAYS_H

/* Draws the rays of the current sparkle or effect as four LINE_G2 segments swept around its screen point. */
/* Each image defines EFFECT_DRAW_WORK as the work record the rays come from. */

MATCH void Effect_DrawSparkleRays(u16 angle, u16 radius) {
    LINE_G2* prim;
    s32      i;

    D_1F800000.view.effect.params[0] = EFFECT_DRAW_WORK->unk_20;
    D_1F800000.view.effect.params[1] = EFFECT_DRAW_WORK->unk_22;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(EFFECT_DRAW_WORK->pos.x.fixed, EFFECT_DRAW_WORK->pos.y.fixed, 2, 12);
    D_1F800000.view.effect.params[4] = EFFECT_DRAW_WORK->timer_05 * 6;
    D_1F800000.view.effect.params[5] = EFFECT_DRAW_WORK->timer_05 * 6;
    D_1F800000.view.effect.params[6] = EFFECT_DRAW_WORK->timer_05 * 6;
    for (i = angle; i < angle + 0x20; i += 8) {
        prim = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[3] = (i & 0x1F) << 7;
        prim->x0                         = D_1F800000.view.effect.params[0];
        prim->y0                         = D_1F800000.view.effect.params[1];
        prim->x1                         = D_1F800000.view.effect.params[0] + (rcos(D_1F800000.view.effect.params[3]) * radius >> 12);
        prim->y1                         = D_1F800000.view.effect.params[1] + (rsin(D_1F800000.view.effect.params[3]) * radius >> 12);
        prim->r0                         = D_1F800000.view.effect.params[4];
        prim->g0                         = D_1F800000.view.effect.params[5];
        prim->b0                         = D_1F800000.view.effect.params[6];
        prim->r1                         = 1;
        prim->g1                         = 1;
        prim->b1                         = 1;
        Area_AddCellPrim(EFFECT_DRAW_WORK->pos.x.fixed, EFFECT_DRAW_WORK->pos.y.fixed, 2, 32);
    }
}

#endif
