#include "area119_13.h"

MATCH void func_801F3324(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       y;
    s32       x;
    s32       y1;
    s32       x1;

    if ((g_AreaDrawFlags & 0x4) == 0) {
        return;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
    GFX_AddPrim(6, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    D_1F800014[0].vx = D_1F800014[1].vx = D_1F800014[2].vx = D_1F800014[3].vx = -0x1F40;
    D_1F800014[0].vy = D_1F800014[2].vy = g_Task->screen_y - 0x2040;
    D_1F800014[1].vy = D_1F800014[3].vy = g_Task->screen_y - 0x2140;
    x                                   = (D_1F800014[0].vx + 0x4000) << 9;
    y                                   = (D_1F800014[0].vy + 0x4000) << 9;
    D_1F800014[0].vz                    = -Area_SampleHeight(x, y) / 2 + 0x40;
    D_1F800014[2].vz                    = -Area_SampleHeight(x, y) / 2 + 0x180;
    x1                                  = (D_1F800014[1].vx + 0x4000) << 9;
    y1                                  = (D_1F800014[1].vy + 0x4000) << 9;
    D_1F800014[1].vz                    = -Area_SampleHeight(x1, y1) / 2 + 0x40;
    D_1F800014[3].vz                    = -Area_SampleHeight(x1, y1) / 2 + 0x180;
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    func_80155560((0x2550 << 16) | 0x127, prim, 1);
    GFX_AddPrim(6, sizeof(POLY_FT4));
}
