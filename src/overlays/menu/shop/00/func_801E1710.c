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

    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 146, 160, 0, CHARACTER_BLOCK->window_style);
    n    = 0;
    y    = task->pos.y;
    list = &CHARACTER_BLOCK->records[task->unk_0A][DECOMP_OFFSETOF(Character, abilities.skill)];
    do {
        if (*list != 0) {
            level   = Char_GetAbilityElement(*list);
            shade   = (n == task->unk_0C) * 2;
            ability = (Ability*)&g_Abilities[*list];
            if (n == task->unk_0B || n == task->unk_0C) {
                func_801AF930((s16)(task->pos.x + 7), (s16)(y + 0x1A), 7, level, ability, ability->cost, 1);
                func_801AF930((s16)(task->pos.x + 7), (s16)(y + 0x18), shade, level, ability, ability->cost, 0);
            } else {
                func_801AF930((s16)(task->pos.x + 7), (s16)(y + 0x1A), 0, level, ability, ability->cost, 0);
            }
        }
        n++;
        y += 13;
        list++;
    } while (n < 10);
    record     = g_Characters[task->unk_0A].name;
    name_width = func_801AF20C(record);
    if ((u8)name_width >= 6) {
        name_width = 5;
    }
    UI_DrawText((task->pos.x - (u32)((u8)name_width * 6 - 72)), (task->pos.y + 7), 0, 5, record);
    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->flags & MENU_LIST_FLAG_TAB_2) ? D_801E5C90 : (u8*)&D_801E5C78, 1);
    UI_DrawSpriteRun(task->pos.x - 8, task->pos.y, (task->flags & MENU_LIST_FLAG_TAB_1) ? D_801E5CB4 : D_801E5CA8, 1);
    flags = task->flags;
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        task->flags = 0;
    } else {
        task->flags = flags - MENU_LIST_FRAME_STEP;
    }
    for (n = 0; n < 9; n++) {
        UI_DrawSprite(task->pos.x + (n + 5) * 8, task->pos.y, 1, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(task->pos.x, task->pos.y + (n + 3) * 8, 4, 1);
    }
    UI_DrawSprite(task->pos.x + 136, task->pos.y + 24, 0x20, 1);
    for (n = 0; n < 15; n++) {
        UI_DrawSprite(task->pos.x + 136, task->pos.y + (n + 4) * 8, 0x21, 1);
    }
    UI_DrawSprite(task->pos.x, task->pos.y + 160, 5, 1);
    UI_DrawSprite(task->pos.x + 136, task->pos.y + 152, 0x22, 1);
    for (n = 0; n < 16; n++) {
        UI_DrawSprite(task->pos.x + (n + 1) * 8, task->pos.y + 160, 6, 1);
    }
}
