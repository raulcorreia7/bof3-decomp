#include "engine/slus/slus.h"

/* emits one 8x8 glyph sprite per non-space byte in the string,
 * advancing eight pixels per byte and wrapping to the next row on newline.
 */
MATCH void UI_DrawGlyphString(s16 x, s16 y, u32 clut, const u8* text) {
    s16 start_x;
    /* FAKE: retail keeps the CLUT argument in s0 across the calls. */
    MATCH_REG(u32, cl, "s0");
    s16 X;
    s16 Y;
    s32 t1;
    s32 v0a;
    s32 v0b;
    u8* p;
    u8  ca;
    u8  cb;
    u8  cc;
    u8* sprite;
    u16 color;
    p  = (u8*)text;
    X  = x;
    Y  = y;
    cl = clut;
    func_8014FC00(0);
    sprite  = g_GfxPrimCursor;
    cl      = cl & 0x3Fu;
    color   = (u16)(cl | 0x7800u);
    start_x = X;
    do {
        cc = *p;
        if (cc == '\n') {
            X = start_x;
            Y += 8;
        } else if ((cc != ' ') && (cc != '\0')) {
            *((u16*)(sprite + 0xE)) = color;
            sprite[0x4]             = 0x80;
            sprite[0x5]             = 0x80;
            sprite[0x6]             = 0x80;
            ca                      = *p;
            t1                      = ((s32)ca) - ' ';
            if (t1 < 0) {
                v0b = ((s32)ca) - 1;
            } else {
                v0b = t1;
            }
            sprite[0xC] = (u8)((t1 - ((v0b >> 5) << 5)) << 3);
            cb          = *p;
            if ((((s32)cb) - ' ') < 0) {
                v0a = ((s32)cb) - 1;
            } else {
                v0a = ((s32)cb) - ' ';
            }
            sprite[0xD]             = (u8)((v0a >> 5) << 3);
            *((s16*)(sprite + 0x8)) = X;
            *((s16*)(sprite + 0xA)) = Y;
            SetSprt8((SPRT_8*)sprite);
            PSX_SET_SEMI_TRANSPARENT(sprite);
            GFX_AddPrim(1, 0x10);
            sprite = g_GfxPrimCursor;
        }
        p += 1;
        X += 8;
    } while ((*p) != '\0');
}
