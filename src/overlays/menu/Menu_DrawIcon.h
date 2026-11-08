/* Draw one 16x8 icon cell from the fixed D8 atlas row. One definition shared
 * by the shop, start, Bate and Shisu overlays; each overlay includes this file
 * where the function sits.
 */
/* func_801D2520 (sisyou), func_801D4564 (bate), func_801D550C (shisu), func_801DA00C (shop), func_801DD504 (start) */
MATCH void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode) {
    SPRT* sprt;
    s32   tpage;
    s32   u;

    tpage = getTPage(0, 1, 960, 0);
    GFX_AddDrawMode(tpage);
    sprt = (SPRT*)g_GfxPrimCursor;
    setWH(sprt, 16, 8);
    sprt->clut = STAGE_PALETTE_CLUT;
    if ((shade_mode & BYTE_MASK) == 0) {
        sprt->r0 = sprt->g0 = sprt->b0 = 0x80;
    } else {
        sprt->r0 = sprt->g0 = sprt->b0 = 0x10;
    }
    sprt->v0 = 216;
    u        = (icon_column & BYTE_MASK) << 4;
    sprt->u0 = u;
    setXY0(sprt, sprite_x, sprite_y);
    SetSprt(sprt);
    SetSemiTrans(sprt, 1);
    GFX_AddPrim(1, sizeof(SPRT));
}
