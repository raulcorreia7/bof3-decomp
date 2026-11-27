#include "engine/slus/slus.h"

/* draws the outlined, rotating fairy portrait: projects the work
 * coordinates, builds the portrait quad and the rotating triangle fan, and
 * restores the matrix stack.
 */
MATCH void func_80167910(void) {
    SVECTOR   rot;
    SVECTOR   axis;
    MATRIX    mtx;
    SVECTOR   pos;
    DVECTOR   sxy;
    long      p;
    long      flag;
    long      sxy2;
    POLY_FT4* poly;
    POLY_G3*  prim;
    s16       sy;
    s16       radius;
    s32       angle;
    s32       i;
    s32       mode;

    SELF_SET(D_8014626C);
    if (D_8014626C[0] & 0x40) {
        return;
    }
    setVector(&pos, (s16)((g_Game.base_x.fixed >> 9) - 0x4000), (s16)((g_Game.base_y.fixed >> 9) - 0x4000), (s16)(-(D_801462AA + 0x80) / 2));
    SELF(Actor)->unk_60   = RotTransPers(&pos, (long*)&sxy, &p, &flag);
    SELF(Actor)->screen_x = sxy.vx;
    SELF(Actor)->screen_y = sxy.vy;
    poly                  = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    sy       = SELF(Actor)->screen_x;
    poly->x0 = sy - 6;
    poly->x1 = sy + 7;
    poly->x2 = poly->x0;
    poly->x3 = poly->x1;
    if (g_FrameCount & 0x8) {
        poly->y0 = SELF(Actor)->screen_y - 27 + (((u32)g_FrameCount >> 1) & 0x3);
    } else {
        poly->y0 = SELF(Actor)->screen_y - 24 - (((u32)g_FrameCount >> 1) & 0x3);
    }
    poly->u0 = 204;
    poly->u1 = 204;
    poly->v1 = 155;
    poly->v0 = poly->v1 + 12;
    poly->v2 = poly->v0;
    setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    poly->y1    = poly->y0;
    poly->y2    = poly->y0 + 24;
    poly->y3    = poly->y2;
    poly->u2    = poly->u0 + 24;
    poly->u3    = poly->u2;
    poly->v3    = poly->v1;
    poly->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = getClut(32, 480);
    if (!(SELF(Actor)->param.unk_0B & 0x1)) {
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_FT4));
    } else {
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_FT4));
    }
    PushMatrix();
    setVector(&axis, 0, 0, 0);
    setVector(&rot, (s16)((SELF(Actor)->pos.x.fixed >> 9) - 0x4000), (s16)((SELF(Actor)->pos.y.fixed >> 9) - 0x4000), (s16)(-COORD_INT(SELF(Actor)->pos.z) / 2));
    RotTransMatrix(&rot, mtx, &flag);
    Camera_SetModelMatrix(&axis, &mtx);
    mode = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 896, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, NULL);
    if (!(SELF(Actor)->param.unk_0B & 0x1)) {
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));
    } else {
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(DR_MODE));
    }
    if (g_FrameCount & 0x8) {
        radius = (s16)(0x38 - ((~((u32)g_FrameCount >> 1) & 0x3) * 2));
    } else {
        radius = (s16)(0x38 - (g_FrameCount & 0x6));
    }
    for (i = 0; i < 32; i++) {
        angle                     = i << 7;
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[0].vz = 0;
        g_ScratchPadVectors[1].vx = (s16)FIXED_MUL(radius, rcos(angle));
        g_ScratchPadVectors[1].vy = (s16)FIXED_MUL(radius, rsin(angle));
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[2].vx = (s16)FIXED_MUL(radius, rcos(angle + 128));
        g_ScratchPadVectors[2].vy = (s16)FIXED_MUL(radius, rsin(angle + 128));
        g_ScratchPadVectors[2].vz = 0;
        prim                      = (POLY_G3*)g_GfxPrimCursor;
        setPolyG3(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &sxy2);
        setRGB0(prim, 0x80, 0x80, 0x80);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        if (!(SELF(Actor)->param.unk_0B & 0x1)) {
            Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_G3));
        } else {
            GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G3));
        }
    }
    PopMatrix();
}
