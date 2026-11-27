#include "shop_00.h"

MATCH void func_801DF6A8(void) {
    u8* cell;
    u8  count;
    u8  record;
    u8  slot;
    u16 x;
    u16 y;

    slot = 0;
    Menu_DrawClutStrip(g_WindowClut);
    count = Party_CountOrder(PARTY_ORDER_FIELD);
    MENU_DRAW_HEADER();
    if (count != 0) {
        do {
            record = g_CharSlot[g_PartyFieldOrder[slot]];
            Menu_DrawCharacterWindow(0x11, (slot * 0x36 + 0x3E) & 0xFFFE, record, (g_Characters[record].party_flags >> 1) & 1, 0);
            TEXT_Format(g_UITextFormatBuffer, D_801D0E60, slot + 1);
            UI_TextDrawGlyphString(26, (s16)(slot * 54 + 67), -((g_Characters[record].party_flags & 2) != 0) & 7, g_UITextFormatBuffer);
            slot += 1;
        } while (slot < count);
    }
    func_801DF00C(0x96, 0x3B);
    if (D_8014865A != 0x7F) {
        cell = &D_801E5BC8[(s8)D_8014865D * 0xC] + D_8014865A * 6;
        if (cell[4] != 0) {
            x = 0x7E;
            y = 0x30;
        } else {
            x = 0x80;
            y = 0x34;
        }
        Menu_DrawCursorFrame(MEM(u16, cell), MEM(u16, cell + 2), x, y, 0, 6);
    }
    cell = &D_801E5BC8[D_80148659 * 0xC] + D_80148658 * 6;
    if (cell[4] != 0) {
        x = 0x7E;
        y = 0x30;
    } else {
        x = 0x80;
        y = 0x34;
    }
    Menu_DrawCursorFrame(MEM(u16, cell), MEM(u16, cell + 2), x, y, 1, 6);
}
