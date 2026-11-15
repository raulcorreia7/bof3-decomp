#include "area100_13.h"

MATCH void func_801F31E8(Point3l* pos, s32 height) {
    DVECTOR  last_inner;
    DVECTOR  last_outer;
    DVECTOR  inner;
    DVECTOR  outer;
    s32      point[3];
    u8       camera[80];
    POLY_G4* prim;
    s32      angle;
    s32      shade;
    u8       i;

    Area_SetCameraMatrix(camera);
    angle    = 0;
    point[0] = pos->x + ((rcos(0) * 0x200) >> 4);
    point[1] = pos->y + ((rsin(0) * 0x200) >> 4);
    point[2] = pos->z;
    Area_ProjectPoint(point, &inner);
    point[2] = pos->z + height;
    Area_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 0x1) << 2) | 0x20;
    for (i = 0; i < AREA_RING_POINTS; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += AREA_RING_ANGLE_STEP;
        point[0] = pos->x + ((rcos((u16)angle) * 0x200) >> 4);
        point[1] = pos->y + ((rsin((u16)angle) * 0x200) >> 4);
        point[2] = pos->z;
        Area_ProjectPoint(point, &inner);
        point[2] = pos->z + height;
        Area_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 960, 0), 0);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(DR_MODE));
        prim = GFX_BeginPolyG4(1);
        setXY4(prim, last_inner.vx, last_inner.vy, last_outer.vx, last_outer.vy, inner.vx, inner.vy, outer.vx, outer.vy);
        setRGB0(prim, shade, shade, shade);
        setRGB1(prim, shade, shade, shade);
        if ((u8)(i - 4) >= 8) {
            shade += 4;
        } else {
            shade -= 4;
        }
        setRGB2(prim, shade, shade, shade);
        setRGB3(prim, shade, shade, shade);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(POLY_G4));
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 960, 0), 0);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(DR_MODE));
    }
}
