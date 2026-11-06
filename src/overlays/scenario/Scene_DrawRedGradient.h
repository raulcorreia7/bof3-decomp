/* func_801D19A8 (sce15ef2), func_801D1BAC (sce15ef3) */
MATCH void Scene_DrawRedGradient(s8 red) {
    POLY_G4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x380, 0x100) & 0xFFFF, NULL);
    GFX_AddPrim(7U, 0xCU);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 0);
    setXY4(prim, 0, 0, 0x140, 0, 0, 0x78, 0x140, 0x78);
    setRGB0(prim, 0, 0, 0);
    setRGB1(prim, 0, 0, 0);
    setRGB2(prim, red, 0, 0);
    setRGB3(prim, red, 0, 0);
    GFX_AddPrim(7U, 0x24U);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 0);
    setXY4(prim, 0, 0x78, 0x140, 0x78, 0, 0xF0, 0x140, 0xF0);
    setRGB0(prim, red, 0, 0);
    setRGB1(prim, red, 0, 0);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(7U, 0x24U);
}
