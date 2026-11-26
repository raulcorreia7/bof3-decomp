/* Draws a small four-point diamond at the screen position (x, y): rotates the points by the area camera angle, projects them and queues one Gouraud quad. */
/* func_801F3ECC (area016), func_801F3E00 (area033), func_801F3ECC (area045), func_801F3F04 (area065), func_801F3F00
   (area087), func_801F4A30 (area088), func_801F3F90 (area104), func_801F3ED0 (area115), func_801F3EE4 (area121),
   func_801F3E3C (area151), func_801F3D90 (area152) */
MATCH void Area_DrawGradientDiamond(s16 x, s16 y) {
    MATRIX   matrix;
    long     depth;
    long     flag;
    POLY_G4* prim;

    PushMatrix();
    RotMatrix(&g_AreaCameraAngle, &matrix);
    matrix.t[0] = 0;
    matrix.t[1] = 0;
    matrix.t[2] = 0;
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    prim = (POLY_G4*)g_GfxPrimCursor;
    setVector(&g_ScratchPadVectors[0], -10, 0, 0);
    setVector(&g_ScratchPadVectors[1], 0, -4, 0);
    setVector(&g_ScratchPadVectors[2], 0, 4, 0);
    setVector(&g_ScratchPadVectors[3], 10, 0, 0);

    SetPolyG4(prim);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    setRGB0(prim, 0xFF, 0, 0);
    setRGB1(prim, 0x80, 0, 0x80);
    setRGB2(prim, 0x80, 0, 0x80);
    setRGB3(prim, 0, 0, 0xFF);
    prim->x0 += x - 0x9E;
    prim->y0 += y - 0x76;
    prim->x1 += x - 0x9E;
    prim->y1 += y - 0x76;
    prim->x2 += x - 0x9E;
    prim->y2 += y - 0x76;
    prim->x3 += x - 0x9E;
    prim->y3 += y - 0x76;

    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    PopMatrix();
}
