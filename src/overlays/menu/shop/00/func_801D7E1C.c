#include "shop_00.h"

/* The per-slot shop byte arrays (stride 0x140), the item records addressed by
 * byte offset (stride 0xA4), the shop caption buffer and the panel helpers are
 * declared by shop_00.h; func_8014F800 is declared by gfx/prim.h. */
MATCH void func_801D7E1C(u8 slot, s32 x, s32 y, s32 style, u8 cursor) {
    u8  item;
    s32 rec;
    /* FAKE: the retail build homes the x copy in s4 and reuses x's s2 for gx;
     * unpinned the allocator merges x and xpos into one pseudo (82.98). */
    MATCH_REG(s32, xpos, "s4");
    s32 sel;
    u32 enabled;
    u32 value;
    s16 gx;
    s16 row_y;
    s32 i;

    enabled = style & BYTE_MASK;
    UI_DrawWindow(x + 3, y + 3, 158, 112, 0, enabled);
    Menu_DrawPanelFrame(x, y, 0x12, 0xD);
    item  = D_80145FCC[slot][0];
    value = g_SaveData.characters[item].level * 10;
    xpos  = x;
    row_y = y + 6;
    if (g_SaveData.zenny < value || g_SaveData.characters[item].inoculations != 0) {
        sel = 7;
    } else {
        sel = -(enabled != 0) & 7;
    }
    i   = 0;
    /* The x - x term keeps x live across the xpos copy, so the allocator keeps
     * the copy instruction instead of merging xpos with x. */
    rec = item * 0xA4 + x - x;
    gx  = xpos + 8;
    do {
        if (((((u8*)&g_SaveData.characters[0].inoculations)[rec] >> (u8)i) & 1) || (u8)i == cursor) {
            UI_DrawText(gx, row_y, 2, 0xFF, Resource_GetText((i & BYTE_MASK) + 0xDE));
        } else {
            UI_DrawText(gx, row_y, sel & BYTE_MASK, 0xFF, Resource_GetText((i & BYTE_MASK) + 0xDE));
        }
        sprintf((char*)g_UiFormatBuffer, D_801D0CDC, value & HALF_MASK);
        g_UiFormatBuffer[3] = 0x60;
        UI_DrawAsciiString((xpos + 112), row_y, sel & BYTE_MASK, g_UiFormatBuffer);
        i++;
        row_y += 0xD;
    } while ((u8)i < 8);
}
