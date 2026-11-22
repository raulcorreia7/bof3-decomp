/* Area_DrawYellowLine (func_801F3ADC in area188, func_801F48E8 in area098). Every change must verify every member. */
MATCH void Area_DrawYellowLine(s32* from, s32* to, u8 intensity) {
    POLY_G4* prim;
    TILE_1*  segment;
    Pos3     current;
    Pos3     step;
    DVECTOR  projected;
    s32      phase;
    u8       i;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(from, &projected);
    setXY2(prim, projected.vx + 1, projected.vy - 1, projected.vx, projected.vy);
    Camera_ProjectPoint(to, &projected);
    prim->x2 = projected.vx + 1;
    prim->y2 = projected.vy - 1;
    prim->x3 = projected.vx;
    prim->y3 = projected.vy;
    setRGB0(prim, 0, 0, 0);
    setRGB1(prim, intensity, intensity, 0);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, intensity, intensity, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(from, &projected);
    setXY2(prim, projected.vx, projected.vy, projected.vx - 1, projected.vy + 1);
    Camera_ProjectPoint(to, &projected);
    prim->x2 = projected.vx;
    prim->y2 = projected.vy;
    prim->x3 = projected.vx - 1;
    prim->y3 = projected.vy + 1;
    setRGB0(prim, intensity, intensity, 0);
    setRGB1(prim, 0, 0, 0);
    setRGB2(prim, intensity, intensity, 0);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));

    step.x    = -0x1000;
    step.y    = -0x400;
    phase     = g_FrameCount & 0xF;
    current.x = to[0] + step.x * phase;
    current.y = to[1] + step.y * phase;
    current.z = to[2];
    for (i = 0; i < 8; i++) {
        if (current.x < from[0]) {
            break;
        }
        Camera_ProjectPoint(&current.x, &projected);
        segment = (TILE*)g_GfxPrimCursor;
        SetTile1(segment);
        SetSemiTrans(segment, 1);
        setXY0(segment, projected.vx, projected.vy);
        setRGB0(segment, intensity, intensity, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, 12);
        current.x += -0x10000;
        current.y += -0x4000;
    }
}
