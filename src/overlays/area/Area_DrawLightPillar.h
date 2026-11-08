/* Draws a pillar of light at pos: sixteen semi-transparent Gouraud quads between a ring of radius 32 at pos and the
 * same ring 0x800 units higher, with a shade that alternates each frame and steps by 4 per segment. One definition
 * shared by the area overlays; every change here must verify every member. */
/* func_801F2DF0 (area036), func_801F30A8 (area059), func_801F3D70 (area100), func_801F3EEC (area112), func_801F2F78
 * (area116), func_801F3FDC (area143), func_801F2E68 (area146) */
MATCH void Area_DrawLightPillar(s32* pos) {
    DVECTOR  last_inner;
    DVECTOR  last_outer;
    DVECTOR  inner;
    DVECTOR  outer;
    s32      point[3];
    u8       camera[0x30];
    POLY_G4* prim;
    s32      angle;
    s32      shade;
    u8       i;

    /* The camera call ignores its argument, so camera stays unused. */
    Area_SetCameraMatrix(pos);
    angle    = 0;
    point[0] = pos[0] + ((rcos(0) * 0x200) >> 4);
    point[1] = pos[1] + ((rsin(0) * 0x200) >> 4);
    point[2] = pos[2];
    Area_ProjectPoint(point, &inner);
    point[2] = pos[2] + 0x8000000;
    Area_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 1) << 2) | 0x20;
    for (i = 0; i < AREA_RING_POINTS; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += AREA_RING_ANGLE_STEP;
        point[0] = pos[0] + ((rcos((u16)angle) * 0x200) >> 4);
        point[1] = pos[1] + ((rsin((u16)angle) * 0x200) >> 4);
        point[2] = pos[2];
        Area_ProjectPoint(point, &inner);
        point[2] = pos[2] + 0x8000000;
        Area_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 960, 0), 0);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY4(prim, last_inner.vx, last_inner.vy, last_outer.vx, last_outer.vy, inner.vx, inner.vy, outer.vx,
               outer.vy);
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
