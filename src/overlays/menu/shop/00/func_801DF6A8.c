#include "shop_00.h"

/* nonmatching unmeasured: tried the first draft cleaned with a typed row loop and FIELD cursor cells. resume: close the
 * +0xC insert (extra store) in the row loop. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DF6A8(void) {
    u8* cell;
    u8  count;
    u8  record;
    u16 x;
    u16 y;
    s32 slot;

    Menu_DrawClutStrip(D_80144953);
    count = Party_CountOrder(PARTY_ORDER_KIND_WALKING);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (count != 0) {
        slot = 0;
        do {
            record = g_CharSlot[g_PartyWalkOrder[slot]];
            Menu_DrawCharacterWindow(0x11, (slot * 0x36 + 0x3E) & 0xFFFE, record,
                                     (g_Characters[record].unk_07 >> 1) & 1, 0);
            sprintf((char*)g_UiFormatBuffer, (char*)D_801D0E60, slot + 1);
            UI_DrawGlyphString(26, (s16)(slot * 54 + 67), -((g_Characters[record].unk_07 & 2) != 0) & 7,
                               g_UiFormatBuffer);
            slot += 1;
        } while (slot < count);
    }
    func_801DF00C(0x96, 0x3B);
    if (D_8014865A != 0x7F) {
        cell = &D_801E5BC8[D_8014865A * 6 + (s8)D_8014865D * 0xC];
        if (cell[4] != 0) {
            x = 0x7E;
            y = 0x30;
        } else {
            x = 0x80;
            y = 0x34;
        }
        Menu_DrawCursorFrame(FIELD(u16, cell, 0), FIELD(u16, cell, 2), x, y, 0, 6);
    }
    cell = &D_801E5BC8[D_80148658 * 6 + D_80148659 * 0xC];
    if (cell[4] != 0) {
        x = 0x7E;
        y = 0x30;
    } else {
        x = 0x80;
        y = 0x34;
    }
    Menu_DrawCursorFrame(FIELD(u16, cell, 0), FIELD(u16, cell, 2), x, y, 1, 6);
}
#else
INCLUDE_ASM(func_801DF6A8);
#endif
