#include "area048_13.h"

#ifdef NON_MATCHING
/* Draws the ground patch at one cell as four Gouraud triangles: the projected centre is the shared
 * vertex and the rim is a diamond whose extent follows the mode's radius byte and the camera angle. */
NON_MATCHING void func_801F4258(s32 mode) {
    POLY_G3* prim;
    s16*     screen;
    long     p;
    long     flag;
    s32      depth;
    s32      cell_x;
    s32      cell_y;
    s32      offset;
    s32      radius;
    s32      color;
    s32      i;

    g_ScratchPadVectors[0].vx = (D_801F4E78[mode] - 0x80) << 7;
    g_ScratchPadVectors[0].vy = (D_801F4E7C[mode] - 0x80) << 7;
    g_ScratchPadVectors[0].vz = -(D_801F4E80[mode] << 3);
    cell_x                    = D_801F4E78[mode] << 16;
    cell_y                    = D_801F4E7C[mode] << 16;
    depth                     = RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &p, &flag);
    if (((u32)(((u16*)D_1F800034)[0] + 0x3C) & HALF_MASK) >= 0x1B9) {
        return;
    }
    if (((u32)(((u16*)D_1F800034)[1] + 0x96) & HALF_MASK) >= 0x1C3) {
        return;
    }
    if (depth == 0) {
        return;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(cell_x, cell_y, 1, sizeof(DR_MODE));
    screen                    = D_1F800034;
    g_ScratchPadVectors[2].vx = screen[0];
    g_ScratchPadVectors[0].vx = screen[0];
    offset                    = 1125 * D_801F4E84[mode] / depth;
    g_ScratchPadVectors[1].vx = screen[0] + offset;
    offset                    = 1125 * D_801F4E84[mode] / depth;
    g_ScratchPadVectors[3].vx = screen[0] - offset;
    g_ScratchPadVectors[3].vy = screen[1];
    g_ScratchPadVectors[1].vy = screen[1];
    radius                    = D_801F4E84[mode] + ABS((D_801F4E84[mode] * rsin(g_AreaCameraAngle.vx)) >> 13);
    offset                    = 1125 * radius / depth;
    g_ScratchPadVectors[2].vy = screen[1] + offset;
    offset                    = 1125 * radius / depth;
    g_ScratchPadVectors[0].vy = screen[1] - offset;
    for (i = 0; i < 4; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = screen[0];
        prim->y0 = screen[1];
        prim->x1 = g_ScratchPadVectors[i].vx;
        prim->y1 = g_ScratchPadVectors[i].vy;
        prim->x2 = g_ScratchPadVectors[(i + 1) & 3].vx;
        prim->y2 = g_ScratchPadVectors[(i + 1) & 3].vy;
        color    = ((D_8014686B << 4) + 0x10) * mode;
        prim->r0 = color | (mode == 0 ? 0x50 : 0);
        prim->g0 = color;
        prim->b0 = (mode == 0 ? 0x50 : 0);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        Area_CellAddPrim(cell_x, cell_y, 1, sizeof(POLY_G3));
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(cell_x, cell_y, 1, sizeof(DR_MODE));
}
#else
INCLUDE_ASM(func_801F4258);
#endif
