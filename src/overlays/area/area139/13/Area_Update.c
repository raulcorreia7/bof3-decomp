#include "area139_13.h"
#include "overlays/area/Area_FloorQuad.h"

#ifdef NON_MATCHING
NON_MATCHING void Area_Update(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       y;
    s32       x;
    s32       y1;
    s32       x1;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
    GFX_AddPrim(6, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    if (g_Task->direction_08 != 0) {
        D_1F800014[0].vy = D_1F800014[1].vy = D_1F800014[2].vy = D_1F800014[3].vy = ((FIX_INT(g_Task->pos.y.fixed) - 0x80) << 7) | 0x40;
        D_1F800014[0].vx = D_1F800014[2].vx = ((FIX_INT(g_Task->pos.x.fixed) - 0x7F) << 7) - (g_Task->screen_y - 0x40);
        D_1F800014[1].vx = D_1F800014[3].vx = ((FIX_INT(g_Task->pos.x.fixed) - 0x80) << 7) - (g_Task->screen_y + 0x40);
    } else {
        D_1F800014[0].vx = D_1F800014[1].vx = D_1F800014[2].vx = D_1F800014[3].vx = ((FIX_INT(g_Task->pos.x.fixed) - 0x80) << 7) | 0x40;
        D_1F800014[0].vy = D_1F800014[2].vy = ((FIX_INT(g_Task->pos.y.fixed) - 0x7F) << 7) + (g_Task->screen_y + 0x40);
        D_1F800014[1].vy = D_1F800014[3].vy = ((FIX_INT(g_Task->pos.y.fixed) - 0x80) << 7) + (s16)(g_Task->screen_y - 0x40);
    }
    x                = (D_1F800014[0].vx + 0x4000) << 9;
    y                = (D_1F800014[0].vy + 0x4000) << 9;
    D_1F800014[0].vz = -Area_SampleHeight(x, y) / 2 + 0x40;
    D_1F800014[2].vz = -Area_SampleHeight(x, y) / 2 + 0x180;
    x1               = (D_1F800014[1].vx + 0x4000) << 9;
    y1               = (D_1F800014[1].vy + 0x4000) << 9;
    D_1F800014[1].vz = -Area_SampleHeight(x1, y1) / 2 + 0x40;
    D_1F800014[3].vz = -Area_SampleHeight(x1, y1) / 2 + 0x180;
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad((g_Task->direction_08 << 21) | AREA_FLOOR_QUAD_PART | (s16)g_Task->screen_x, prim, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, -2, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(Area_Update);
#endif
