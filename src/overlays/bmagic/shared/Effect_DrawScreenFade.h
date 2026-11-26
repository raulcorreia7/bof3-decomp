MATCH void Effect_DrawScreenFade(void) {
    s8       shade;
    POLY_G4* prim;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    prim  = (POLY_G4*)g_GfxPrimCursor;
    shade = SELF(PartyMember)->unk_09 * 0x10;
    SetPolyG4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    setXY4(prim, 0, 0, 0x13F, 0, 0, 0x78, 0x13F, 0x78);
    PSX_SET_NEUTRAL_RGB(prim);
    setRGB1(prim, 128, 128, 128);
    setRGB2(prim, shade, shade, shade);
    setRGB3(prim, shade, shade, shade);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    setXY4(prim, 0, 0x78, 0x13F, 0x78, 0, 0x167, 0x13F, 0x167);
    setRGB0(prim, shade, shade, shade);
    setRGB1(prim, shade, shade, shade);
    setRGB2(prim, 128, 128, 128);
    setRGB3(prim, 128, 128, 128);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(GFX_LAYER_UI, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}
