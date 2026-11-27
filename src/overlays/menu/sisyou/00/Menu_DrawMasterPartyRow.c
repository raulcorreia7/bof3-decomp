#include "sisyou_00.h"

MATCH void Menu_DrawMasterPartyRow(u16 x, u16 y, u8 entry, u8 icon) {
    Character* record;
    u8*        base;
    s16        text_x;
    s16        text_y;
    u32        value;
    s32        align;

    base = &g_WindowStyle;
    UI_WindowDraw((x + 3), (y + 3), MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, 0, base[0]);
    /* FAKE: the record base is formed straight from the byte symbol; folding the offset through the pointer local
     * places the address pair too early. */
    record = (Character*)(&g_WindowStyle + 0x16) + entry;
    Menu_DrawPortrait((x + 86), (y + 0x2), record->character_id, ((record->status >> 6) & 2));
    UI_TextDraw((x + 20), (y + 3), 0, CHARACTER_NAME_LENGTH, (u8*)record);
    TEXT_Format(g_UITextFormatBuffer, D_801D0C04, record->level);
    UI_TextDrawGlyphString((x + 22), (y + 23), 0, g_UITextFormatBuffer);

    /* Retail reads the status halfword and the next one as a word. */
    if ((LOWU(record->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_TextDrawString((x + 46), (y + 23), 1, MENU_LABEL_LENGTH, g_MenuLabelPoison);
        } else {
            UI_TextDrawString((x + 46), (y + 23), 1, MENU_LABEL_LENGTH, g_MenuLabelConfusion);
        }
    } else if (record->status & STATUS_POISONED) {
        UI_TextDrawString((x + 46), (y + 23), 1, MENU_LABEL_LENGTH, g_MenuLabelPoison);
    } else if (record->status & STATUS_CONFUSED) {
        UI_TextDrawString((x + 46), (y + 23), 1, MENU_LABEL_LENGTH, g_MenuLabelConfusion);
    }

    value = record->hp;
    align = (record->status >> 11) & 0x4;
    if (value < 2U) {
        align = 2;
    }
    TEXT_Format(g_UITextFormatBuffer, g_MenuCurrentValueFormat, value);
    text_x = (x + 22);
    text_y = (y + 31);
    UI_TextDrawGlyphString(text_x, text_y, align, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuMaxValueFormat, record->stats.max_hp);
    UI_TextDrawGlyphString(text_x, text_y, 0, g_UITextFormatBuffer);

    align = ((record->stats.max_ap >> 2) >= record->ap) ? 4 : 0;
    if (record->ap == 0) {
        align = 2;
    }
    TEXT_Format(g_UITextFormatBuffer, g_MenuCurrentValueFormat, record->ap);
    text_y = (y + 39);
    UI_TextDrawGlyphString(text_x, text_y, align, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuMaxValueFormat, record->stats.max_ap);
    UI_TextDrawGlyphString(text_x, text_y, 0, g_UITextFormatBuffer);

    UI_SpriteDrawRun(x, y, D_801D3F58, 0);
    Menu_DrawExperienceLine((x + 20), (y + 18), entry, record->level, record->exp);
    GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    Menu_DrawPanelIcon((x + 9), (y + 5), (u8)(icon + 3), 30, GetClut(16, STAGE_PALETTE_Y), 128);
}
