#include "area041_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F34AC(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    u16*      sxy;
    long      p;
    long      flag;
    s32       i;

    if (D_801F4334[g_Task->timer] != 0) {
        func_801F387C(D_801F4334[g_Task->timer] << 4);
    } else {
        func_801F3704();
    }

    quad = D_1F800014;
    sxy  = (u16*)D_1F800034;
    for (i = 0; i < 0xE; i += 2) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad->vx = g_Task->pos.x.fixed + D_801F4344[i] * 0x80 + (s8)D_801F4354[i] * g_Task->timer * 8;
        quad->vy = g_Task->pos.y.fixed + D_801F4344[i + 1] * 0x80 + (s8)D_801F4354[i + 1] * g_Task->timer * 8;
        quad->vz = COORD_INT(g_Task->pos.z);
        RotTransPers(quad, (long*)sxy, &p, &flag);
        prim->x0 = prim->x2 = sxy[0] - g_Task->timer;
        prim->y0 = prim->y1 = SP_REF(u16, 0x36) - g_Task->timer;
        prim->x1 = prim->x3 = sxy[0] + g_Task->timer;
        prim->y2 = prim->y3 = SP_REF(u16, 0x36) + g_Task->timer;
        Area_ApplyTileToQuad(((0xD - g_Task->timer) << 19) + ((0xBA00u << 16) | 0x9124u), prim, 1);
        Area_AddCellPrim((g_Task->pos.x.fixed + AREA_CELL_ORIGIN) << 9, (g_Task->pos.y.fixed + AREA_CELL_ORIGIN) << 9, 6, sizeof(POLY_FT4));
    }

    g_Task->timer += 1;
    if (g_Task->timer >= 0xE) {
        g_Task->header.step += 1;
    }
}
#else
INCLUDE_ASM(func_801F34AC);
#endif
