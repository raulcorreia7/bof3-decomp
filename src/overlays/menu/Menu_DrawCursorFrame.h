/* func_801D1CC0 (sisyou), func_801D3384 (bate), func_801D432C (shisu), func_801D8E2C (shop), func_801DC324 (start) */
MATCH void Menu_DrawCursorFrame(u16 x, u16 y, s32 width, s32 height, u8 color, s32 frame_mode) {
    u8       rgb[3];
    u8       base;
    u8       i;
    s32      width_copy;
    s32      bit;
    s32      state;
    s32      mask;
    LINE_F3* line3;
    LINE_F4* line4;

    width_copy = width; /* FAKE: width_copy steers prologue copy order. */
    mask       = (u8)frame_mode;

    if (color != 0) {
        state = g_FrameCount;
        if (state & 8) {
            base = (u8)((state & 6) << 5 | 0x3F);
        } else {
            base = (u8)((~state & 6) << 5 | 0x3F);
        }
    } else {
        base = 0xFF;
    }

    for (bit = 1, i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++, bit <<= 1) {
        if (bit & mask) {
            rgb[i] = base;
        } else {
            rgb[i] = 0;
        }
    }

    line3 = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(line3);
    setXY3(line3, x + 4, y, x, y + 4, x, y + height - 1);
    setRGB0(line3, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(1, sizeof(LINE_F3));

    line4 = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line4);
    setXY0(line4, x + 4, y);
    line4->x3 = x;
    line4->y3 = y + height - 1;
    line4->y1 = y;
    line4->y2 = y + height - 1;
    line4->x1 = (line4->x2 = x + width_copy - 1);
    setRGB0(line4, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(1, sizeof(LINE_F4));
}
