#include "start_08.h"

extern u8 D_80148656; /* local: u8 read; a sibling copy is s8 */

/* Draws the ten-row ability list panel: each row's ability with its level, the title label, the two tab strips and the
 * window frame. */
/* func_801E0354 */
MATCH void Menu_DrawAbilitiesPanel(MenuPanelTask* task) {
    u8* text;
    u8* entry;
    s32 disabled;
    s32 color;
    s32 level;
    s32 ability;
    s16 label_x;
    u16 y;
    u8  flags;
    u8  n;

    UI_WindowDraw(task->pos.vx + 3, task->pos.vy + 3, 154, 160, 0, g_WindowStyle);
    text = Party_GetAbilities(task->unk_0A, task->unk_0B, 0);
    y    = task->pos.vy;
    for (n = 0; n < 10; n++, y += 13, text++) {
        if (*text != 0) {
            disabled = (u8)func_801AF5B0(task->unk_08, D_80148656, *text) == 0;
            color    = -disabled & 0x7;
            if (n == task->flags) {
                color = 2;
            }
            level   = Char_AbilityGetElement(*text);
            entry   = (u8*)&g_Abilities[*text];
            ability = Char_AbilityGetCost(g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], *text, 0);
            if (n == task->flags || n == task->unk_0C) {
                if ((u8)color != 7) {
                    UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x1A), UI_TEXT_DIM, level, entry, ability, 1);
                }
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x18), color, level, entry, ability, disabled);
            } else {
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x1A), color, level, entry, ability, disabled);
            }
        }
    }
    label_x = (u16)task->pos.vx + 0x4E - strlen((const char*)D_801ECC98[task->unk_0B]) * 4;
    UI_TextDraw(label_x, (task->pos.vy + 7), 0, MENU_LABEL_LENGTH, (u8*)(D_801ECC98[task->unk_0B]));
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, (task->unk_09 & 0x2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, (task->unk_09 & 0x1) ? g_MenuListTab1OnSprites : g_MenuListTab1OffSprites, UI_SPRITE_ALT_PAGE);
    flags = task->unk_09;
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        task->unk_09 = 0;
    } else {
        task->unk_09 = flags - MENU_LIST_FRAME_STEP;
    }
    for (n = 0; n < 10; n++) {
        UI_SpriteDraw(task->pos.vx + (n + 5) * 8, task->pos.vy, 1, UI_SPRITE_ALT_PAGE);
    }
    for (n = 0; n < 17; n++) {
        UI_SpriteDraw(task->pos.vx, task->pos.vy + (n + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + 24, 0x20, UI_SPRITE_ALT_PAGE);
    for (n = 0; n < 15; n++) {
        UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + (n + 4) * 8, 0x21, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx, task->pos.vy + 160, 5, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + 152, 0x22, UI_SPRITE_ALT_PAGE);
    if ((s16)task->u.list.tabs != 0) {
        UI_SpriteDraw(task->pos.vx + 8, task->pos.vy, 0x32, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(task->pos.vx + 144, task->pos.vy, 0x34, UI_SPRITE_ALT_PAGE);
    }
    for (n = 0; n < 17; n++) {
        UI_SpriteDraw(task->pos.vx + (n + 1) * 8, task->pos.vy + 160, 6, UI_SPRITE_ALT_PAGE);
    }
}
