/* Draws the same pillar of light as Area_DrawLightPillar, with the camera matrix in a local of its own. Every change must verify every member. */
/* func_801F3980 (area145), func_801F2D60 (area100) */
MATCH void Area_DrawMatrixLightPillar(s32* pos) {
    DVECTOR  last_inner;
    DVECTOR  last_outer;
    DVECTOR  inner;
    DVECTOR  outer;
    s32      point[3];
    MATRIX   matrix;
    u8       camera[48];
    POLY_G4* prim;
    s32      angle;
    s32      shade;
    u8       i;

    /* The retail frame holds 48 bytes after the matrix that no statement uses. */
    Camera_SetMatrix(&matrix);
    angle    = 0;
    point[0] = pos[0] + ((rcos(0) * 0x200) >> 4);
    point[1] = pos[1] + ((rsin(0) * 0x200) >> 4);
    point[2] = pos[2];
    Camera_ProjectPoint(point, &inner);
    point[2] = pos[2] + TO_COORD(2048);
    Camera_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 1) << 2) | 0x20;
    for (i = 0; i < AREA_RING_POINTS; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += AREA_RING_ANGLE_STEP;
        point[0] = pos[0] + ((rcos((u16)angle) * 0x200) >> 4);
        point[1] = pos[1] + ((rsin((u16)angle) * 0x200) >> 4);
        point[2] = pos[2];
        Camera_ProjectPoint(point, &inner);
        point[2] = pos[2] + TO_COORD(2048);
        Camera_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
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
        Area_CellAddPrim(point[0], point[1], 0, sizeof(POLY_G4));
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
    }
}
