/* Draw a 40x48 portrait from the 4-byte atlas records. One definition shared by
 * the shop, start, Bate, Shisu and commu overlays; each overlay includes this
 * file where the function sits and binds g_MenuPortraitAtlas in its
 * table in config/symbols.toml.
 */
/* func_801D23A0 (sisyou), func_801D3518 (bate), func_801D44C0 (shisu), func_801D8F8C (commu02), func_801D8FC0 (shop),
   func_801DC4B8 (start) */
MATCH void Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode) {
    SPRT* sprt;
    u8*   entry;
    s32   shade;
    s32   tpage;
    u16   clut;

    entry = g_MenuPortraitAtlas + (atlas_index & BYTE_MASK) * 4;

    tpage = getTPage(0, 0, 896, 256);
    GFX_AddDitheredDrawMode(1, tpage);

    sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);

    shade = shade_mode & BYTE_MASK;
    if (shade == 0) {
        sprt->b0 = 128;
        sprt->g0 = 128;
        sprt->r0 = 128;
    } else if (shade == 1) {
        sprt->b0 = 48;
        sprt->g0 = 48;
        sprt->r0 = 48;
    } else {
        sprt->g0 = 64;
        sprt->r0 = 64;
        sprt->b0 = 128;
    }

    setXY0(sprt, sprite_x, sprite_y);
    setUV0(sprt, entry[0], entry[1]);
    clut = getClut(entry[2], entry[3] + 0x1E0);
    setWH(sprt, 40, 48);
    sprt->clut = clut;
    GFX_AddPrim(1, sizeof(SPRT));
}
