#include "shop_00.h"

/* Draws the ability stock panel: the stocked abilities with their icon rows,
 * the tab strips, the count and the window frame. */
MATCH void func_801E112C(MenuPanelTask* task) {
    u8       row_offset;
    u8       count;
    u8       offset;
    u8       shade;
    u8       i;
    u16      y;
    s32      mask;
    s32      level;
    s32      title_x;
    u8*      types;
    Ability* ability;

    UI_WindowDraw((task->pos.vx + 3) & HALF_MASK, (task->pos.vy + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_WINDOW_HEIGHT, 0, CHARACTER_BLOCK->window_style);
    /* The ability stock begins 0xB1A bytes past the window style the panel block opens with. */
    types = MEM_PTR(u8, CHARACTER_BLOCK) + 0xB1A + (UI_ScrollList(&task->unk_0A, &row_offset, &count, MEM_PTR(u8, &task->flags)) & BYTE_MASK);
    y     = task->pos.vy + (s8)row_offset;
    for (i = 0; i < count + 9; i++) {
        if (*types != 0) {
            ability = (Ability*)&g_Abilities[*types];
            mask    = ((u32)task->flags >> 4) ^ 0xF;
            mask    = (mask != 0) ? -1 : 0;
            offset  = count & mask;
            level   = Char_AbilityGetElement(*types);
            shade   = (task->unk_0A + i == task->unk_0C + offset) * 2;
            if (task->unk_0A + i == task->unk_0B + offset || task->unk_0A + i == task->unk_0C + offset) {
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x1A), UI_TEXT_DIM, level, ability, ability->cost, 1);
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x18), shade, level, ability, ability->cost, 0);
            } else {
                UI_ListDrawAbilityRow((s16)(task->pos.vx + 7), (s16)(y + 0x1A), 0, level, ability, ability->cost, 0);
            }
        }
        types++;
        y += 13;
    }
    UI_WindowDraw((task->pos.vx + 3) & HALF_MASK, (task->pos.vy + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_TOP_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    UI_WindowDraw((task->pos.vx + 3) & HALF_MASK, (task->pos.vy + 146) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_BOTTOM_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    title_x = (Game_ReadCommand(D_801E5D1C) & BYTE_MASK) * 4 - 0x4E;
    UI_TextDraw((task->pos.vx - title_x), (task->pos.vy + 7), 0, MENU_LABEL_LENGTH, D_801E5D1C);
    TEXT_Format(g_UITextFormatBuffer, D_801D0E7C, Party_CountAbilities(CHAR_INDEX_RYU, 0xFF, 0) & BYTE_MASK, 0x80);
    UI_TextDrawGlyphString((task->pos.vx + 85), (task->pos.vy + 146), 0, g_UITextFormatBuffer);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, D_801E5C78, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, D_801E5C84, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 10; i++) {
        UI_SpriteDraw(task->pos.vx + (i + 5) * 8, task->pos.vy, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 15; i++) {
        UI_SpriteDraw(task->pos.vx, task->pos.vy + (i + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + 24, 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 12; i++) {
        UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + (i + 5) * 8, 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + 136, 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(task->pos.vx, task->pos.vy + 144, 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw(task->pos.vx + (i + 1) * 8, task->pos.vy + 144, 0x1A, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 80, task->pos.vy + 144, 0x1B, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 6; i++) {
        UI_SpriteDraw(task->pos.vx + (i + 11) * 8, task->pos.vy + 144, 0x1C, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 136, task->pos.vy + 144, 0x1D, UI_SPRITE_ALT_PAGE);
    UI_ListDrawScrollbar(D_8014546C, task->unk_0A, task->pos.vx + 0x90, task->pos.vy + 0x18, 9, 0x80, 0x74);
}
