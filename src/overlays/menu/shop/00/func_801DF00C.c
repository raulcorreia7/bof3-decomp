#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DF00C(s32 x, s32 y) {
    Character* record;
    s16        base_x;
    s16        base_y;
    u8         row;
    u8         highlight;
    u32        clut;
    u32        index;

    Menu_DrawWindowFrame(x, y, 0x12, 0x15);
    base_x    = x + 7;
    base_y    = y + 6;
    highlight = 0;
    for (row = 0; row < D_801E6250; row++) {
        clut   = 0;
        record = &g_Characters[g_CharSlot[D_801E6244[row]]];
        UI_WindowDraw(base_x, base_y, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, UI_WINDOW_OPEN_TOP_LEFT, g_WindowStyle);
        Menu_DrawCharacterPortrait(x + 0x5D, base_y, record->character_id, highlight ? 1 : (record->status >> 6) & 2);
        index = clut & BYTE_MASK;
        UI_TextDraw(base_x + 20, base_y + 1, index, CHARACTER_NAME_LENGTH, record);
        Menu_DrawIcon(base_x + 2, base_y + 0x15, 3, D_801D0E78[0]);
        TEXT_Format(g_UiTextFormatBuffer, D_801D0E64, record->level);
        UI_TextDrawGlyphString(x + 0x1F, base_y + 0x15, index, g_UiTextFormatBuffer);
        if ((LOWU(record->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
            if (g_FrameCount & 0x20) {
                UI_TextDrawString(base_x + 0x30, base_y + 0x15, index != 0 ? index : 1, MENU_LABEL_LENGTH, D_801E5C68);
            } else {
                UI_TextDrawString(base_x + 0x30, base_y + 0x15, index != 0 ? index : 1, MENU_LABEL_LENGTH, D_801E5C70);
            }
        } else if (record->status & STATUS_POISONED) {
            UI_TextDrawString(base_x + 0x30, base_y + 0x15, index != 0 ? index : 1, MENU_LABEL_LENGTH, D_801E5C68);
        } else if (record->status & STATUS_CONFUSED) {
            UI_TextDrawString(base_x + 0x30, base_y + 0x15, index != 0 ? index : 1, MENU_LABEL_LENGTH, D_801E5C70);
        }
        Menu_DrawIcon(base_x + 2, base_y + 0x1D, 0, 0);
        if (!highlight) {
            if (record->status & STATUS_LOW_HP)
                clut = 4;
            if (record->hp < 2)
                clut = 2;
        } else {
            clut = 7;
        }
        TEXT_Format(g_UiTextFormatBuffer, D_801D0E68, record->hp);
        UI_TextDrawGlyphString(x + 0x1F, base_y + 0x1D, clut, g_UiTextFormatBuffer);
        clut = highlight ? 7 : (record->fatigue != 0) * 4;
        TEXT_Format(g_UiTextFormatBuffer, D_801D0E70, record->stats.max_hp);
        UI_TextDrawGlyphString(x + 0x1F, base_y + 0x1D, clut, g_UiTextFormatBuffer);
        Menu_DrawIcon(base_x + 2, base_y + 0x25, 1, 0);
        clut = 0;
        if (!highlight) {
            if ((record->stats.max_ap >> 2) >= record->ap)
                clut = 4;
            if (record->ap == 0)
                clut = 2;
        } else {
            clut = 7;
        }
        TEXT_Format(g_UiTextFormatBuffer, D_801D0E68, record->ap);
        UI_TextDrawGlyphString(x + 0x1F, base_y + 0x25, clut, g_UiTextFormatBuffer);
        TEXT_Format(g_UiTextFormatBuffer, D_801D0E70, record->stats.max_ap);
        UI_TextDrawGlyphString(x + 0x1F, base_y + 0x25, 0, g_UiTextFormatBuffer);
        base_y += 0x34;
    }
}
#else
INCLUDE_ASM(func_801DF00C);
#endif
