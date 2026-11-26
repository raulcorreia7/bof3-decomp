#include "start_08.h"

/* Draws the party summary rows of the character panel: each listed slot's window,
 * portrait, name, level, status label and HP/AP values. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EAA14(MenuPanelTask* task) {
    Character* character;
    u8*        item;
    u8         count;
    u16        portrait_x;
    s16        label_x;
    s16        stat_x;
    u16        x;
    u16        y;
    u8         color;
    u8         text_color;
    u8         shaded;

    Menu_DrawWindowFrame(task->pos.x, task->pos.y, 0x12, 0x15);
    count = 0;
    x     = task->pos.x + 7;
    y     = task->pos.y + 6;
    item  = (u8*)task->item_table;
    if (task->unk_0A == 0) {
        return;
    }
    portrait_x = (task->pos.x + 0x5D) & HALF_MASK;
    label_x    = task->pos.x + 0x37;
    stat_x     = task->pos.x + 0x1F;
    do {
        character = &g_Characters[g_CharSlot[*item]];
        shaded    = 1;
        if (character->party_flags & 2) {
            color = UI_TEXT_DIM;
        } else {
            shaded = 0;
            color  = 0;
        }
        UI_WindowDraw(x, y, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, (u8)(shaded + 0x80), g_WindowStyle);
        Menu_DrawCharacterPortrait(portrait_x, y, character->character_id, shaded == 0 ? (character->status >> 6) & 2 : 1);
        text_color = color;
        UI_TextDraw((s16)(x + 20), (s16)(y + 1), text_color, CHARACTER_NAME_LENGTH, (u8*)character);
        Menu_DrawIcon((x + 2) & HALF_MASK, (y + 0x15) & HALF_MASK, 3, shaded);
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F18, character->level);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x15), text_color, g_UiTextFormatBuffer);
        if ((LOWU(character->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
            if (g_FrameCount & 0x20) {
                UI_TextDrawString(label_x, (s16)(y + 0x15), text_color != 0 ? text_color : 1, MENU_LABEL_LENGTH, D_801ED5D4);
            } else {
                UI_TextDrawString(label_x, (s16)(y + 0x15), text_color != 0 ? text_color : 1, MENU_LABEL_LENGTH, D_801ED5DC);
            }
        } else if (character->status & STATUS_POISONED) {
            UI_TextDrawString(label_x, (s16)(y + 0x15), text_color != 0 ? text_color : 1, MENU_LABEL_LENGTH, D_801ED5D4);
        } else if (character->status & STATUS_CONFUSED) {
            UI_TextDrawString(label_x, (s16)(y + 0x15), text_color != 0 ? text_color : 1, MENU_LABEL_LENGTH, D_801ED5DC);
        }
        Menu_DrawIcon((x + 2) & HALF_MASK, (y + 0x1D) & HALF_MASK, 0, shaded);
        if (shaded == 0) {
            if (character->status & STATUS_LOW_HP) {
                color = 4;
            }
            if (character->hp < 2) {
                color = 2;
            }
        } else {
            color = UI_TEXT_DIM;
        }
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F1C, character->hp);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x1D), color, g_UiTextFormatBuffer);
        if (shaded == 0) {
            color = (character->fatigue != 0) * 4;
        } else {
            color = UI_TEXT_DIM;
        }
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F24, character->stats.max_hp);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x1D), color, g_UiTextFormatBuffer);
        Menu_DrawIcon((x + 2) & HALF_MASK, (y + 0x25) & HALF_MASK, 1, shaded);
        color = -(s32)shaded & UI_TEXT_DIM;
        if (shaded == 0) {
            if ((character->stats.max_ap >> 2) >= character->ap) {
                color = 4;
            }
            if (character->ap == 0) {
                color = 2;
            }
        } else {
            color = UI_TEXT_DIM;
        }
        count++;
        item++;
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F1C, character->ap);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x25), color, g_UiTextFormatBuffer);
        color = -(s32)shaded & UI_TEXT_DIM;
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F24, character->stats.max_ap);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x25), color, g_UiTextFormatBuffer);
        y += 0x34;
    } while (count < task->unk_0A);
}
#else
INCLUDE_ASM(func_801EAA14);
#endif
