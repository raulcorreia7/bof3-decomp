/* The 8-pixel window frame of the camp, battle-camp, master and shop menus: start/08, bate/00, shisu/00 and
 * shop/00 include it where the function sits. */
/* func_801DF6EC (start), func_801D674C (bate), func_801D76F4 (shisu), func_801DC1F4 (shop) */
MATCH void Menu_DrawWindowFrame(s16 x, s16 y, u8 width, u8 height) {
    RECT window;
    /* FAKE: retail reserves 8 bytes of frame that no statement uses. */
    FAKE_STACK_PADS(u8, 8);
    SPRT* sprite;
    s16   columns;
    s16   rows;

    /* the top edge */
    window.x = 112;
    window.y = 152;
    window.h = 8;
    window.w = 8;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 832, 256), &window);
    GFX_AddPrim(1, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + 16, y);
    setUV0(sprite, 0, 0);
    setWH(sprite, (width - 4) * 8, 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(1, sizeof(SPRT));

    /* the bottom edge */
    window.x = 152;
    window.y = 160;
    window.h = 8;
    window.w = 8;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 832, 256), &window);
    GFX_AddPrim(1, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + 16, y + (height - 1) * 8);
    setUV0(sprite, 0, 0);
    setWH(sprite, (width - 4) * 8, 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(1, sizeof(SPRT));

    /* the left edge */
    window.x = 176;
    window.y = 152;
    window.h = 8;
    window.w = 8;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 832, 256), &window);
    GFX_AddPrim(1, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x, y + 16);
    setUV0(sprite, 0, 0);
    setWH(sprite, 8, (height - 4) * 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(1, sizeof(SPRT));

    /* the right edge */
    window.x = 176;
    window.y = 160;
    window.h = 8;
    window.w = 8;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 832, 256), &window);
    GFX_AddPrim(1, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + (width - 1) * 8, y + 16);
    setUV0(sprite, 0, 0);
    setWH(sprite, 8, (height - 4) * 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(1, sizeof(SPRT));

    /* the body */
    window.x = 112;
    window.y = 160;
    window.h = 8;
    window.w = 8;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 832, 256), &window);
    GFX_AddPrim(1, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + 8, y + 8);
    setUV0(sprite, 0, 0);
    setWH(sprite, (width - 2) * 8, (height - 2) * 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(1, sizeof(SPRT));

    /* back to the full texture window */
    window.y = 0;
    window.x = 0;
    window.h = 256;
    window.w = 256;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 832, 256), &window);
    GFX_AddPrim(1, sizeof(DR_MODE));

    /* the corners */
    UI_DrawSprite(x, y, 0x23, 1);
    columns = width - 2;
    UI_DrawSprite(x + columns * 8, y, 0x26, 1);
    rows = height - 2;
    UI_DrawSprite(x, y + rows * 8, 0x27, 1);
    UI_DrawSprite(x + columns * 8, y + rows * 8, 0x29, 1);
}
