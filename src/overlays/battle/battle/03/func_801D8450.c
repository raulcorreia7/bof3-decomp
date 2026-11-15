#include "battle_03.h"

MATCH void func_801D8450(u32 panel_index) {
    u8  index;
    s16 x;
    u16 y;
    u16 color;
    u8  r;
    u8  g;
    u8  b;

    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    index = panel_index;
    /* FAKE: byte-offset read of the frame origin; the array-subscript
     * form shifts the RTL insn numbering and the scheduler sinks the call
     * constants past the frame loads. */
    x     = *(s16*)((u8*)D_801EAEE8 + index * 8);
    y     = D_801EAEE8[index].unk_02;
    /* FAKE: retail reads g_WindowStyle as s8. */
    color = *(u16*)(MEM_PTR(u8, 0x80033A08u) + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;
    Battle_DrawWindowTile(x, (y + 2), 5, 1);
    func_801D9AB4(x, y, 10, 1);
    func_801D9AB4(x, (y + 0x11), 11, 1);
    func_801DA5A8((x + 2), (y + 2), (x + 0x25), (y + 2), r, g, b);
    func_801DA5A8((x + 2), (y + 3), (x + 2), (y + 0x10), r, g, b);
    func_801DA4B4((x + 0x25), (y + 2), (x + 0x25), (y + 0x10), r, g, b);
    func_801DA4B4((x + 2), (y + 0x10), (x + 0x25), (y + 0x10), r, g, b);
    UI_DrawText((x + 8), (y + 3), 0, 8, (u8*)(D_801EAEB0 + index * 2u));
}
