#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D8C58(s16 x, s16 y, u8 index, u8 flag) {
    u8* slot;
    s16 tx;
    s32 value;
    /* FAKE: retail reserves 24 frame bytes (0x18..0x2F) no statement uses. */
    FAKE_STACK_PADS(u8, 24);
    slot = &g_WindowStyle;
    UI_DrawWindow(x + 3, y + 3, 101, 37, 0, slot[0]);
    slot += index * 0xA4;
    slot += 0x16;
    if (flag == 0) {
        tx = x + 0x2C;
    } else {
        tx = x + 0x26;
    }
    if (flag == 0) {
        UI_DrawText(tx, y + 7, 0, TEXT_LENGTH_MAX, &D_801E5844);
    } else {
        UI_DrawText(tx, y + 7, 0, TEXT_LENGTH_MAX, &D_801E5848);
    }
    if (flag == 0) {
        value = FIELD(s32, slot, 0x8);
    } else {
        value = Char_GetExpForLevel(index, (FIELD(u8, slot, 0x6) + 1) & BYTE_MASK);
    }
    if (value != -1) {
        TEXT_Format(g_UiFormatBuffer, g_MenuExperienceFormat, value);
    } else {
        TEXT_FormatLiteral(g_UiFormatBuffer, g_MenuExperienceBlank);
    }
    UI_DrawAsciiString(x + 21, y + 26, 0, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, D_801E5680, 1);
}
#else
INCLUDE_ASM(func_801D8C58);
#endif
