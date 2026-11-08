/* Draw the five-row CLUT strip, two 0x20-wide columns per row. One definition
 * shared by the shop, start and shisu overlays; each image binds the entry, index and
 * 4-byte cell tables in its table in config/symbols.toml and the image header declares them.
 */
/* func_801DBD24 (shop), func_801DF21C (start), func_801D7224 (shisu) */
MATCH void Menu_DrawClutStrip(u8 clut_index) {
    u16     cluts[4];
    u16*    clut;
    SPRT*   prim;
    u8*     entry;
    UvRect* desc;
    s16     x;
    s16     y;
    s32     index;
    /* FAKE: retail keeps the constant shade byte in s5. */
    MATCH_REG(u8, shade, "s5");
    u8 h;
    u8 row;
    u8 pair;

    GFX_AddDrawMode(GetTPage(0, 0, 832, 256));
    cluts[0] = GetClut(48, STAGE_PALETTE_Y + 2);
    cluts[1] = GetClut(80, STAGE_PALETTE_Y + 2);
    cluts[2] = GetClut(64, STAGE_PALETTE_Y + 2);
    cluts[3] = GetClut(96, STAGE_PALETTE_Y + 2);
    index    = clut_index & BYTE_MASK;
    clut     = (u16*)((index << 1) + (u32)cluts);
    x        = 0;
    for (row = 0; row < 5; row++) {
        entry = &MENU_CLUT_STRIP_ENTRIES[MENU_CLUT_STRIP_PALETTES[index]];
        for (pair = 0; pair < 2; pair++, x += 0x20) {
            y     = 0;
            shade = 0x80;
            do {
                prim = (SPRT*)g_GfxPrimCursor;
                SetSprt(prim);
                SetSemiTrans(prim, 0);
                setXY0(prim, x, y);
                prim->clut = *clut;
                desc       = &MENU_CLUT_STRIP_CELLS[*entry];
                setUV0(prim, desc->u, desc->v);
                prim->w = desc->w;
                h       = desc->h;
                setRGB0(prim, shade, shade, shade);
                prim->h = h;
                GFX_AddPrim(1, sizeof(SPRT));
                y += desc->h;
                entry++;
            } while (y < 240);
        }
    }
}
