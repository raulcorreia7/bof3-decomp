#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_index, s32 shaded, s32 unused) {
    Character* records;
    Character* stats;
    u32        clut;
    u32        text_clut;
    s32        text_y;
    s32        x;
    s32        y;

    clut = (u8)shaded ? 7 : 0;
    UI_DrawWindow(px + 3, py + 3, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, (u8)shaded, CHARACTER_BLOCK->window_style);
    x = px;
    y = py;
    /* FAKE: the order lock keeps the x and y copies below the window call. */
    FAKE_ORDER_LOCK_BEGIN
        records = (Character*)CHARACTER_BLOCK->records;
        px += 0x56;
        py += 2;
        stats = &records[character_index];
        Menu_DrawCharacterPortrait(px, py, stats->character_id, (u8)shaded == 0 ? (stats->status >> 6) & 2 : 1);
        text_clut = clut & BYTE_MASK;
        UI_DrawText(x + 20, y + 3, text_clut, 5, stats);
    FAKE_ORDER_LOCK_END;
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, stats->level);
    text_y = (s16)(y + 0x17);
    UI_DrawGlyphString(x + 22, text_y, text_clut, g_UiFormatBuffer);
    if ((*(u32*)&stats->status & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E5814);
        } else {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E581C);
        }
    } else if (stats->status & STATUS_POISONED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E5814);
    } else if (stats->status & STATUS_CONFUSED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E581C);
    }
    if (stats->hp < (u32)(stats->stats.max_hp >> 2)) {
        stats->status |= STATUS_LOW_HP;
    } else {
        stats->status &= ~STATUS_LOW_HP;
    }
    if ((u8)shaded == 0) {
        if (stats->status & STATUS_LOW_HP) {
            clut = 4;
        }
        if (stats->hp < 2) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, g_MenuCurrentValueFormat, stats->hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    if ((u8)shaded == 0) {
        clut = (stats->fatigue != 0) * 4;
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, g_MenuMaxValueFormat, stats->stats.max_hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    if ((u8)shaded == 0) {
        if (stats->ap < (u32)(stats->stats.max_ap >> 2)) {
            clut = 4;
        }
        if (stats->ap == 0) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, g_MenuCurrentValueFormat, stats->ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    TEXT_Format(g_UiFormatBuffer, g_MenuMaxValueFormat, stats->stats.max_ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, D_801E547C, 0);
    Menu_DrawExperienceLine(x + 0x14, y + 0x12, character_index, stats->level, stats->exp);
    /* FAKE: dead stores keep px and py the CSE heads of their x and y copies. */
    px = 0;
    py = 0;
}
#else
INCLUDE_ASM(Menu_DrawCharacterWindow);
#endif
