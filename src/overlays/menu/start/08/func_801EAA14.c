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
    s32        x;
    s32        y;
    s32        colour;
    u8         text_colour;
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
            colour = UI_TEXT_DIM;
        } else {
            shaded = 0;
            colour = 0;
        }
        UI_WindowDraw(x & HALF_MASK, y & HALF_MASK, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, (shaded + 0x80) & BYTE_MASK, g_WindowStyle);
        Menu_DrawCharacterPortrait(portrait_x, y & HALF_MASK, character->character_id, shaded == 0 ? (character->status >> 6) & 2 : 1);
        text_colour = colour & BYTE_MASK;
        UI_TextDraw((s16)(x + 20), (s16)(y + 1), text_colour, CHARACTER_NAME_LENGTH, (u8*)character);
        Menu_DrawIcon((x + 2) & HALF_MASK, (y + 0x15) & HALF_MASK, 3, shaded);
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F18, character->level);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x15), text_colour, g_UiTextFormatBuffer);
        if ((LOWU(character->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
            if (g_FrameCount & 0x20) {
                UI_TextDrawString(label_x, (s16)(y + 0x15), text_colour != 0 ? text_colour : 1, MENU_LABEL_LENGTH, D_801ED5D4);
            } else {
                UI_TextDrawString(label_x, (s16)(y + 0x15), text_colour != 0 ? text_colour : 1, MENU_LABEL_LENGTH, D_801ED5DC);
            }
        } else if (character->status & STATUS_POISONED) {
            UI_TextDrawString(label_x, (s16)(y + 0x15), text_colour != 0 ? text_colour : 1, MENU_LABEL_LENGTH, D_801ED5D4);
        } else if (character->status & STATUS_CONFUSED) {
            UI_TextDrawString(label_x, (s16)(y + 0x15), text_colour != 0 ? text_colour : 1, MENU_LABEL_LENGTH, D_801ED5DC);
        }
        Menu_DrawIcon((x + 2) & HALF_MASK, (y + 0x1D) & HALF_MASK, 0, shaded);
        if (shaded == 0) {
            if (character->status & STATUS_LOW_HP) {
                colour = 4;
            }
            if (character->hp < 2) {
                colour = 2;
            }
        } else {
            colour = UI_TEXT_DIM;
        }
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F1C, character->hp);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x1D), colour, g_UiTextFormatBuffer);
        if (shaded == 0) {
            colour = (character->fatigue != 0) * 4;
        } else {
            colour = UI_TEXT_DIM;
        }
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F24, character->stats.max_hp);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x1D), colour, g_UiTextFormatBuffer);
        Menu_DrawIcon((x + 2) & HALF_MASK, (y + 0x25) & HALF_MASK, 1, shaded);
        colour = -(s32)shaded & UI_TEXT_DIM;
        if (shaded == 0) {
            if ((character->stats.max_ap >> 2) >= character->ap) {
                colour = 4;
            }
            if (character->ap == 0) {
                colour = 2;
            }
        } else {
            colour = UI_TEXT_DIM;
        }
        item++;
        count++;
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F1C, character->ap);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x25), colour, g_UiTextFormatBuffer);
        colour = -(s32)shaded & UI_TEXT_DIM;
        TEXT_Format(g_UiTextFormatBuffer, D_801D0F24, character->stats.max_ap);
        UI_TextDrawGlyphString(stat_x, (s16)(y + 0x25), colour, g_UiTextFormatBuffer);
        y += 0x34;
    } while (count < task->unk_0A);
}
#else
INCLUDE_ASM(func_801EAA14);
#endif
