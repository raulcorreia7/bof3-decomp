#include "batl_end_00.h"

u32 Char_GetExpToNextLevel(s32 slot);

#ifdef NON_MATCHING
NON_MATCHING void func_801F07E0(void) {
    u8  i;
    u8  y;
    u8* buffer;
    u8* text;

    y = 0x2C;
    func_801F039C(0x14, 0x28, 0x118, g_MenuCurrentPanel->unk_09);
    if (g_Battle.party_count != 0) {
        i      = 0;
        buffer = (u8*)g_TextVariables[2];
        do {
            text = g_Game.members[i].chr.name;
            UI_DrawText(0x19, y, 0, 5, text);
            if (g_Game.members[i].chr.level != 0x63) {
                sprintf((char*)buffer, D_801EEC44, Char_GetExpToNextLevel(i));
                UI_DrawAsciiString(0x50, y, 0, buffer);
                UI_DrawText(0x85, y, 0, 0xFF, Message_GetText(0x15));
                sprintf((char*)buffer, D_801EEC48, g_Game.members[i].chr.level + 1);
                UI_DrawAsciiString(0x118, y, 0, buffer);
            } else {
                UI_DrawText(0x55, y, 0, 0xFF, Message_GetText(0x41));
            }
            i++;
            y += 0x10;
        } while (i < g_Battle.party_count);
    }
}
#else
INCLUDE_ASM(func_801F07E0);
#endif
