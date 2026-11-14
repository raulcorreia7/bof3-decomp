#include "engine/slus/slus.h"

/* emits one 8x8 glyph sprite per non-space byte in the string,
 * advancing eight pixels per byte and wrapping to the next row on newline.
 */
MATCH void UI_DrawGlyphString(s16 x, s16 y, u32 clut, const u8* text) {
    s16 start_x;
    /* FAKE: retail keeps the CLUT argument in s0 across the calls. */
    FAKE_REG(u32, cl, "s0");
    s16     X;
    s16     Y;
    s32     t1;
    s32     v0a;
    s32     v0b;
    u8*     p;
    u8      ca;
    u8      cb;
    u8      cc;
    SPRT_8* sprite;
    u16     color;
    p  = (u8*)text;
    X  = x;
    Y  = y;
    cl = clut;
    func_8014FC00(0);
    sprite  = (SPRT_8*)g_GfxPrimCursor;
    cl      = cl & 0x3Fu;
    color   = (cl | STAGE_PALETTE_CLUT);
    start_x = X;
    do {
        cc = *p;
        if (cc == '\n') {
            X = start_x;
            Y += 8;
        } else if ((cc != ' ') && (cc != '\0')) {
            sprite->clut = color;
            setRGB0(sprite, 0x80, 0x80, 0x80);
            ca = *p;
            t1 = (ca) - ' ';
            if (t1 < 0) {
                v0b = (ca)-1;
            } else {
                v0b = t1;
            }
            sprite->u0 = ((t1 - ((v0b >> 5) << 5)) << 3);
            cb         = *p;
            if (((cb) - ' ') < 0) {
                v0a = (cb)-1;
            } else {
                v0a = (cb) - ' ';
            }
            sprite->v0 = ((v0a >> 5) << 3);
            setXY0(sprite, X, Y);
            SetSprt8(sprite);
            SetSemiTrans(sprite, 1);
            GFX_AddPrim(1, sizeof(SPRT_8));
            sprite = (SPRT_8*)g_GfxPrimCursor;
        }
        p += 1;
        X += 8;
    } while ((*p) != '\0');
}
