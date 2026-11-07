#include "sisyou_00.h"

MATCH void Master_DrawPartyRow(u16 x, u16 y, u8 entry, u8 icon) {
    Character* record;
    u8*        base;
    s16        text_x;
    s16        text_y;
    u32        value;
    s32        align;

    base = &g_WindowStyle;
    UI_DrawWindow((x + 3), (y + 3), 125, 48, 0, base[0]);
    /* FAKE: the record base is formed straight from the byte symbol; folding the offset through the pointer local
     * places the address pair too early. */
    record = (Character*)(&g_WindowStyle + 0x16) + entry;
    Menu_DrawPortrait((x + 0x56), (y + 2), record->character_id, ((record->status >> 6) & 2));
    UI_DrawText((x + 20), (y + 3), 0, 5, (u8*)record);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, record->level);
    UI_DrawGlyphString((x + 22), (y + 23), 0, g_UiFormatBuffer);

    /* Retail reads the status halfword and the next one as a word. */
    if ((LOWU(record->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_DrawTextString((x + 46), (y + 23), 1, 0x10, g_MenuLabelPoison);
        } else {
            UI_DrawTextString((x + 46), (y + 23), 1, 0x10, g_MenuLabelConfusion);
        }
    } else if (record->status & STATUS_POISONED) {
        UI_DrawTextString((x + 46), (y + 23), 1, 0x10, g_MenuLabelPoison);
    } else if (record->status & STATUS_CONFUSED) {
        UI_DrawTextString((x + 46), (y + 23), 1, 0x10, g_MenuLabelConfusion);
    }

    value = record->hp;
    align = (record->status >> 11) & 4;
    if (value < 2U) {
        align = 2;
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C08, value);
    text_x = (x + 0x16);
    text_y = (y + 0x1F);
    UI_DrawGlyphString(text_x, text_y, align, g_UiFormatBuffer);
    TEXT_Format(g_UiFormatBuffer, D_801D0C10, record->stats.max_hp);
    UI_DrawGlyphString(text_x, text_y, 0, g_UiFormatBuffer);

    align = ((record->stats.max_ap >> 2) >= record->ap) ? 4 : 0;
    if (record->ap == 0) {
        align = 2;
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C08, record->ap);
    text_y = (y + 0x27);
    UI_DrawGlyphString(text_x, text_y, align, g_UiFormatBuffer);
    TEXT_Format(g_UiFormatBuffer, D_801D0C10, record->stats.max_ap);
    UI_DrawGlyphString(text_x, text_y, 0, g_UiFormatBuffer);

    UI_DrawSpriteRun(x, y, D_801D3F58, 0);
    Menu_DrawExperienceLine((x + 0x14), (y + 0x12), entry, record->level, record->exp);
    GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    Menu_DrawPanelIcon((x + 9), (y + 5), (u8)(icon + 3), 0x1E, GetClut(16, 480), 128);
}
