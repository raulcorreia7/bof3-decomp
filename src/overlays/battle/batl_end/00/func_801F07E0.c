#include "batl_end_00.h"

MATCH void func_801F07E0(void) {
    u8 i;
    /* FAKE: retail keeps the row coordinate in s5 across the panel call. */
    FAKE_REG(u8, y, "s5");
    u8* buffer;
    u8* text;

    y = 0x2C;
    func_801F039C(0x14, 0x28, 0x118, g_UIPanelCurrent->unk_09);
    /* FAKE: keep the row coordinate live across the panel call. */
    FAKE_USE(y);
    if (g_Battle.party_count != 0) {
        i      = 0;
        buffer = (u8*)g_TextVariables[2];
        do {
            text = g_Game.members[i].chr.name;
            UI_TextDraw(0x19, y, 0, 5, text);
            if (g_Game.members[i].chr.level != 0x63) {
                sprintf((char*)buffer, D_801EEC44, Char_GetExpToNextLevel(i));
                UI_TextDrawAscii(0x50, y, 0, buffer);
                UI_TextDraw(0x85, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(0x15));
                sprintf((char*)buffer, D_801EEC48, g_Game.members[i].chr.level + 1);
                UI_TextDrawAscii(0x118, y, 0, buffer);
            } else {
                UI_TextDraw(0x55, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(0x41));
            }
            i++;
            y += 0x10;
        } while (i < g_Battle.party_count);
    }
}
