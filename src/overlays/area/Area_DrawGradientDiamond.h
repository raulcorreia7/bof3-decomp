/* Draws a small four-point diamond at the screen position (x, y): rotates
 * the points by the area camera angle, projects them and
 * queues one Gouraud quad. One definition shared by the area overlays; every
 * change here must verify every member. */
/* func_801F3ECC (area016), func_801F3E00 (area033), func_801F3ECC (area045), func_801F3F04 (area065), func_801F3F00 (area087), func_801F4A30 (area088), func_801F3F90 (area104), func_801F3ED0 (area115), func_801F3EE4 (area121), func_801F3E3C (area151), func_801F3D90 (area152) */
MATCH void Area_DrawGradientDiamond(s16 x, s16 y) {
    MATRIX matrix;
    long   depth;
    long   flag;
    /* FAKE: MATCH_REG pins the scratch base to the retail s1 load. */
    MATCH_REG(SVECTOR*, scratch, "s1");
    SVECTOR* q1;
    SVECTOR* q2;
    SVECTOR* q3;
    s16      vx0;
    /* FAKE: pins the hoisted first-pair loads to the retail v1/v0. */
    MATCH_REG(s16, vy0, "v0");
    u32 primitive;

    PushMatrix();
    RotMatrix(&g_AreaCameraAngle, &matrix);
    matrix.t[0] = 0;
    matrix.t[1] = 0;
    matrix.t[2] = 0;
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    scratch   = D_1F800014;
    primitive = (u32)g_GfxPrimCursor;

    q1 = scratch + 1;
    q2 = scratch + 2;
    q3 = scratch + 3;

    scratch[0].vx           = -10;
    VOL(s16, scratch[0].vy) = 0;
    VOL(s16, scratch[0].vz) = 0;
    VOL(s16, q1->vx)        = 0;
    VOL(s16, q1->vy)        = -4;
    VOL(s16, q1->vz)        = 0;
    VOL(s16, q2->vx)        = 0;
    VOL(s16, q2->vy)        = 4;
    VOL(s16, q2->vz)        = 0;
    VOL(s16, q3->vx)        = 10;
    VOL(s16, q3->vy)        = 0;
    VOL(s16, q3->vz)        = 0;

    SetPolyG4((POLY_G4*)primitive);
    RotTransPers4((SVECTOR*)scratch, (SVECTOR*)(scratch + 1), (SVECTOR*)(scratch + 2), (SVECTOR*)(scratch + 3),
                  (long*)(primitive + 8), (long*)(primitive + 0x10), (long*)(primitive + 0x18),
                  (long*)(primitive + 0x20), &depth, &flag);

    vx0 = *MATCH_VOLATILE_PTR(s16, (primitive + 8));

    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0xC))  = 0x80u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0xE))  = 0x80u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0x14)) = 0x80u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0x16)) = 0x80u;
    vy0                                         = *MATCH_VOLATILE_PTR(s16, (primitive + 10));

    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 4))    = 0xFFu;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 5))    = 0u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 6))    = 0u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0xD))  = 0u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0x15)) = 0u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0x1C)) = 0u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0x1D)) = 0u;
    /* FAKE: volatile-drop keeps the original load and store order. */
    *MATCH_VOLATILE_PTR(u8, (primitive + 0x1E)) = 0xFFu;

    ((POLY_G4*)primitive)->x0 = (s16)(vx0 - 0x9E) + x;
    ((POLY_G4*)primitive)->y0 = (s16)(vy0 - 0x76) + y;
    ((POLY_G4*)primitive)->x1 = (s16)((s16)((POLY_G4*)primitive)->x1 - 0x9E) + x;
    ((POLY_G4*)primitive)->y1 = (s16)((s16)((POLY_G4*)primitive)->y1 - 0x76) + y;
    ((POLY_G4*)primitive)->x2 = (s16)((s16)((POLY_G4*)primitive)->x2 - 0x9E) + x;
    ((POLY_G4*)primitive)->y2 = (s16)((s16)((POLY_G4*)primitive)->y2 - 0x76) + y;
    ((POLY_G4*)primitive)->x3 = (s16)((s16)((POLY_G4*)primitive)->x3 - 0x9E) + x;
    ((POLY_G4*)primitive)->y3 = (s16)((s16)((POLY_G4*)primitive)->y3 - 0x76) + y;

    GFX_AddPrim(1u, 0x24u);
    PopMatrix();
}
