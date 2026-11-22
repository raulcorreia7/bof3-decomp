/* Draws a menu header bar at (x, y): a left cap, two middle halves and a right cap of font-page quads in the window style's palette, then the window frame inside it. */
/* Menu_DrawHeaderBar in area008/13, bate, commu02/08, scena12, shisu, shop, sisyou and start/08. */
/* The grey of the header bar's quads. */
#define MENU_HEADER_GREY 172

MATCH void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    RECT*     window;
    POLY_FT4* prim;
    u16       left;
    u16       top;
    s32       inner;
    s32       clut_x;
    u8        bottom_v;
    s32       bottom_row;
    u16       odd_w;
    s32       outer;
    u16       outer_w;
    s32       half;
    u16       half_w;
    s32       odd;
    s32       right;

    window          = GFX_CURSOR(RECT);
    g_GfxPrimCursor = (u8*)(window + 1);
    setRECT(window, 0, 240, 16, 16);
    left = x;
    top  = y;
    SetDrawMode(GFX_CURSOR(DR_MODE), 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    prim = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    clut_x     = (window_style << 5) + 0x10;
    inner      = x + 2;
    bottom_row = height + 1;
    bottom_v   = bottom_row;
    setXYWH(prim, left, top, 2, bottom_row);
    setUVWH(prim, 0, 0, 2, bottom_row);
    setRGB0(prim, MENU_HEADER_GREY, MENU_HEADER_GREY, MENU_HEADER_GREY);
    prim->y0 += 2;
    prim->y2 -= 3;
    prim->v0 += 2;
    prim->v2 -= 3;
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    outer       = width + 1;
    outer_w     = outer;
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    half = (outer_w - 4) >> 1;
    odd  = (width - 3) & 1;
    prim = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    half_w = half;
    setXY4(prim, inner, top, half + inner, top, inner, top + bottom_row, half + inner, top + bottom_row);
    setUVWH(prim, 0, 0, half_w, bottom_row);
    setRGB0(prim, MENU_HEADER_GREY, MENU_HEADER_GREY, MENU_HEADER_GREY);
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    odd_w       = odd;
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    prim = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, x + half + 2, top, half + odd, bottom_row);
    setUVWH(prim, 0, 0, half_w + odd_w, bottom_row);
    setRGB0(prim, MENU_HEADER_GREY, MENU_HEADER_GREY, MENU_HEADER_GREY);
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    prim = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    /* Open-coded: setXYWH stores the right cap in another order and the bytes differ. */
    right    = x + outer;
    prim->x0 = right - 2;
    prim->y2 = top + bottom_row;
    prim->v2 = bottom_v;
    prim->x1 = right;
    prim->y1 = top;
    prim->x3 = right;
    prim->x2 = right - 2;
    prim->y3 = top + bottom_row;
    prim->y0 = top;
    setUV0(prim, 0, 0);
    prim->u1 = 2;
    prim->v1 = 0;
    prim->u2 = 0;
    prim->u3 = 2;
    prim->v3 = bottom_v;
    setRGB0(prim, MENU_HEADER_GREY, MENU_HEADER_GREY, MENU_HEADER_GREY);
    prim->y1 += 2;
    prim->y2--;
    prim->y3 -= 3;
    prim->v1 += 2;
    prim->v2--;
    prim->v3 -= 3;
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    window          = GFX_CURSOR(RECT);
    g_GfxPrimCursor = (u8*)(window + 1);
    setRECT(window, 0, 0, 256, 256);
    SetDrawMode(GFX_CURSOR(DR_MODE), 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    UI_WindowDrawFrame(x + 2, y + 2, width - 4, height - 4, 0);
}
