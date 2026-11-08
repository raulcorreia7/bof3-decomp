MATCH void Effect_DrawScreenFade(void) {
    s8       shade;
    POLY_G4* prim;

    GFX_AddDitheredDrawMode(1U, getTPage(0, 1, 320, 256));
    prim  = (POLY_G4*)g_GfxPrimCursor;
    shade = g_Task->unk_09 * 0x10;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, 0x13F, 0, 0, 0x78, 0x13F, 0x78);
    setRGB0(prim, 128, 128, 128);
    setRGB1(prim, 128, 128, 128);
    setRGB2(prim, shade, shade, shade);
    setRGB3(prim, shade, shade, shade);
    GFX_AddPrim(1U, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0x78, 0x13F, 0x78, 0, 0x167, 0x13F, 0x167);
    setRGB0(prim, shade, shade, shade);
    setRGB1(prim, shade, shade, shade);
    setRGB2(prim, 128, 128, 128);
    setRGB3(prim, 128, 128, 128);
    GFX_AddPrim(1U, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(1U, getTPage(0, 0, 320, 256));
}
