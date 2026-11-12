#include "shop_00.h"

MATCH void func_801DEE64(void) {
    u8  count;
    u8  slot;
    u8  id;
    s32 row_y;
    u8* counter;
    u8* counter_end;

    count = Party_CountOrder(PARTY_ORDER_FIELD);
    for (slot = 0; slot < count; slot++) {
        counter = &D_80148654;
        row_y   = slot * 0x36;
        id      = g_CharSlot[g_PartyFieldOrder[slot]];
        Menu_DrawCharacterWindow((0x11 - (*counter * 0x28)) & HALF_MASK, (row_y + 0x3E) & 0xFFFE, id, g_Characters[id].unk_07 & 0x2, 0);
        TEXT_Format(g_UiFormatBuffer, D_801D0E60, slot + 1);
        row_y += 0x43;
        UI_DrawGlyphString(26 - (*counter * 40), row_y, 0U, g_UiFormatBuffer);
    }
    /* FAKE: second pointer local for the post-loop use, pure-C best 85.85%. */
    counter_end = &D_80148654;
    func_801DF00C(((*counter_end * 0x2D) + 0x96) & HALF_MASK, 0x3B);
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x12 - (*counter_end * 8)) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
}
