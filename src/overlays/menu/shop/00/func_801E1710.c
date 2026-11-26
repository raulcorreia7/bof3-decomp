#include "shop_00.h"

/* Draws the skill-ability list panel of one character: ten rows with each
 * ability and its level, the name, the two tab strips and the window frame. */
MATCH void func_801E1710(MenuPanelTask* task) {
    Ability* ability;
    u8*      list;
    u8*      record;
    s32      level;
    u8       shade;
    s32      name_width;
    u16      y;
    u8       flags;
    u8       n;

    UI_WindowDraw((task->pos.vx + 3) & HALF_MASK, (task->pos.vy + 3) & HALF_MASK, 146, 160, 0, CHARACTER_BLOCK->window_style);
    n    = 0;
    y    = task->pos.vy;
    list = &CHARACTER_BLOCK->records[task->unk_0A][DECOMP_OFFSETOF(Character, abilities.skill)];
    do {
        if (*list != 0) {
            level   = Char_AbilityGetElement(*list);
            shade   = (n == task->unk_0C) * 2;
            ability = (Ability*)&g_Abilities[*list];
            if (n == task->unk_0B || n == task->unk_0C) {
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x1A), UI_TEXT_DIM, level, ability, ability->cost, 1);
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x18), shade, level, ability, ability->cost, 0);
            } else {
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x1A), 0, level, ability, ability->cost, 0);
            }
        }
        n++;
        y += 13;
        list++;
    } while (n < 10);
    record     = g_Characters[task->unk_0A].name;
    name_width = Game_ReadCommand(record);
    if ((u8)name_width >= 6) {
        name_width = 5;
    }
    UI_TextDraw((task->pos.vx - (u32)((u8)name_width * 6 - 72)), (task->pos.vy + 7), 0, CHARACTER_NAME_LENGTH, record);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, (task->flags & MENU_LIST_FLAG_TAB_2) ? D_801E5C90 : (u8*)&D_801E5C78, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.vx - 8, task->pos.vy, (task->flags & MENU_LIST_FLAG_TAB_1) ? D_801E5CB4 : D_801E5CA8, UI_SPRITE_ALT_PAGE);
    flags = task->flags;
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        task->flags = 0;
    } else {
        task->flags = flags - MENU_LIST_FRAME_STEP;
    }
    for (n = 0; n < 9; n++) {
        UI_SpriteDraw(task->pos.vx + (n + 5) * 8, task->pos.vy, 1, UI_SPRITE_ALT_PAGE);
    }
    for (n = 0; n < 17; n++) {
        UI_SpriteDraw(task->pos.vx, task->pos.vy + (n + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 136, task->pos.vy + 24, 0x20, UI_SPRITE_ALT_PAGE);
    for (n = 0; n < 15; n++) {
        UI_SpriteDraw(task->pos.vx + 136, task->pos.vy + (n + 4) * 8, 0x21, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx, task->pos.vy + 160, 5, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(task->pos.vx + 136, task->pos.vy + 152, 0x22, UI_SPRITE_ALT_PAGE);
    for (n = 0; n < 16; n++) {
        UI_SpriteDraw(task->pos.vx + (n + 1) * 8, task->pos.vy + 160, 6, UI_SPRITE_ALT_PAGE);
    }
}
