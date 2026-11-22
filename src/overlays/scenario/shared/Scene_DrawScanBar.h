/* Draws one scan bar as two semi-transparent gradient quads across the screen above and below its line. */
/* Scene_DrawScanBar (sce15ef2, sce15ef3) */
MATCH void Scene_DrawScanBar(ScanBar* bar) {
    POLY_G4* poly;
    u8       parity;
    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    parity = g_FrameCount & 1;
    poly   = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 0);
    setXY4(poly, 0, bar->y - bar->half_height - parity, 320, bar->y - bar->half_height - parity, 0, bar->y, 320, bar->y);
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 128, 0, 0);
    setRGB3(poly, 128, 0, 0);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 0);
    setXY4(poly, 0, bar->y, 320, bar->y, 0, bar->y + (bar->half_height + parity), 320, bar->y + (bar->half_height + parity));
    setRGB0(poly, 128, 0, 0);
    setRGB1(poly, 128, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
}
