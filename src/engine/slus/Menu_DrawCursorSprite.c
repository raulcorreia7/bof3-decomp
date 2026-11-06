#include "engine/slus/slus.h"

/* draws the front-end panel cursor at (x - 0x16, y + 2) as a 0x18 x 0xC textured sprite with the
 * 0x7802 CLUT: the draw mode and a 12-byte primitive first, then the Sprt and its 0x14-byte slot.
 */
MATCH void Menu_DrawCursorSprite(u16 x, u16 y, s32 unused) {
    SPRT* sprite;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, 0x3C0, 0), (RECT*)0);
    GFX_AddPrim(0, 0xC);
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x - 22, y + 2);
    setUV0(sprite, 204, 156);
    setWH(sprite, 24, 12);
    setRGB0(sprite, 128, 128, 128);
    sprite->clut = 0x7802;
    GFX_AddPrim(0, 0x14);
}
