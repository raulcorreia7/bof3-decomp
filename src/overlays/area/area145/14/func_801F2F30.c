#include "area145_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2F30(s32* first, s32* second) {
    DVECTOR  screen;
    VECTOR   vertex;
    MATRIX   camera;
    LINE_F2* prim;
    u16      tpage;
    s32      vz;
    s32      delta;
    u8       i;

    Area_SetCameraMatrix(&camera);
    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_ADD_DITHERED_DRAW_MODE(1, tpage);

    memcpy(&vertex, first, sizeof(vertex));
    vz = vertex.vz;
    Area_ProjectPoint(&vertex.vx, &screen);

    i = 1;
    do {
        prim = GFX_CURSOR(LINE_F2);
        SetLineF2(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = screen.vx;
        prim->y0 = screen.vy;
        delta    = second[0] - first[0];
        if (delta < 0) {
            delta += 15;
        }
        vertex.vx += delta >> 4;
        delta = second[1] - first[1];
        if (delta < 0) {
            delta += 15;
        }
        vertex.vz = vz;
        vertex.vy += delta >> 4;
        if (i < 16) {
            vertex.vz = vertex.vz - 0x800000 + ((rand() & 0xFFF) << 12);
        }
        Area_ProjectPoint(&vertex.vx, &screen);
        prim->x1 = screen.vx;
        prim->y1 = screen.vy;
        setRGB0(prim, 0x80, 0x80, 0x80);
        GFX_AddPrim(1, sizeof(LINE_F2));
        func_801F311C(prim->x0, prim->y0, prim->x1, prim->y1);
        i++;
    } while (i < 17);
}
#else
INCLUDE_ASM(func_801F2F30);
#endif
