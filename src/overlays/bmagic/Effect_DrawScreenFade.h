MATCH void Effect_DrawScreenFade(void) {
    s8       shade;
    POLY_G4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0xA5 : 0x35, NULL);
    GFX_AddPrim(1U, 0xCU);
    prim  = (POLY_G4*)g_GfxPrimCursor;
    shade = g_Task->unk_09 * 0x10;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, 0x13F, 0, 0, 0x78, 0x13F, 0x78);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setRGB1(prim, 0x80, 0x80, 0x80);
    setRGB2(prim, shade, shade, shade);
    setRGB3(prim, shade, shade, shade);
    GFX_AddPrim(1U, 0x24U);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0x78, 0x13F, 0x78, 0, 0x167, 0x13F, 0x167);
    setRGB0(prim, shade, shade, shade);
    setRGB1(prim, shade, shade, shade);
    setRGB2(prim, 0x80, 0x80, 0x80);
    setRGB3(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(1U, 0x24U);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x25 : 0x15, NULL);
    GFX_AddPrim(1U, 0xCU);
}
