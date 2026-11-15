#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E112C(MenuPanelTask* task) {
    Ability* ability_obj;
    u8*      kinds;
    u8       row_offset;
    u8       count;
    u8       ability_id;
    u8       ability_kind;
    u16      row_y;
    s16      icon_x;
    s16      icon_y;
    s32      index;
    s32      has_icon;
    s32      offset;
    s32      icon_kind;
    s32      ability;

    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_WINDOW_HEIGHT, 0, (s32)g_WindowStyle);
    kinds = &g_WindowStyle + 0xB1A;
    kinds = &kinds[func_801AFD10(&task->u.addr.unk_10, &row_offset, &count, &task->u.addr.unk_12) & BYTE_MASK];
    row_y = task->pos.y + (s8)row_offset;
    if ((count + 9) != 0) {
        index = 0;
        do {
            ability_id = *kinds;
            if (ability_id != 0) {
                offset       = task->flags;
                offset       = (offset >> 4) ^ 0xF;
                offset       = (offset != 0) ? -1 : 0;
                offset       = count & offset;
                icon_x       = task->unk_0A + (index & BYTE_MASK);
                offset       = offset & BYTE_MASK;
                has_icon     = (icon_x ^ (task->unk_0C + offset)) < 1;
                ability_obj  = &g_Abilities[ability_id];
                ability_kind = Char_GetAbilityElement((s32)ability_id);
                if ((icon_x == task->unk_0B + offset) || has_icon) {
                    func_801AF930((s16)(task->pos.x + 7), (s16)(row_y + 0x1A), 7, ability_kind, ability_obj, (s32)ability_obj->cost, 1);
                    icon_y    = (s16)(row_y + 0x18);
                    icon_kind = has_icon * 2;
                    ability   = ability_kind & BYTE_MASK;
                } else {
                    icon_y    = (s16)(row_y + 0x1A);
                    icon_kind = 0;
                    ability   = ability_kind & BYTE_MASK;
                }
                func_801AF930((s16)(task->pos.x + 7), icon_y, icon_kind, ability, ability_obj, (s32)ability_obj->cost, 0);
            }
            kinds += 1;
            index += 1;
            row_y += 0xD;
        } while ((index & BYTE_MASK) < (count + 9));
    }
    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_TOP_HEIGHT, (s32)task->unk_09, (s32)g_WindowStyle);
    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 146) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_BOTTOM_HEIGHT, (s32)task->unk_09, (s32)g_WindowStyle);
    UI_DrawText((s16)(task->pos.x - (((Game_ReadCommand(&D_801E5D1C) & BYTE_MASK) * 4) - 78)), (s16)(task->pos.y + 7), 0, 0x10U, (&D_801E5D1C));
    TEXT_Format(g_UiFormatBuffer, D_801D0E7C, Party_CountAbilities(0U, 0xFFU, 0U) & BYTE_MASK, 0x80);
    UI_DrawGlyphString((s16)(task->pos.x + 85), (s16)(task->pos.y + 146), 0U, g_UiFormatBuffer);
    UI_DrawSpriteRun((s16)task->pos.x, (s16)task->pos.y, &D_801E5C78, 1);
    UI_DrawSpriteRun((s16)task->pos.x, (s16)task->pos.y, &D_801E5C84, 1);
    index = 0;
    do {
        ability = index & BYTE_MASK;
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + ((ability + 5) * 8)), (s16)task->pos.y, 1, 1);
    } while ((index & BYTE_MASK) < 0xAU);
    index = 0;
    do {
        ability = index & BYTE_MASK;
        index += 1;
        UI_DrawSprite((s16)task->pos.x, (s16)(task->pos.y + ((ability + 3) * 8)), 4, 1);
    } while ((index & BYTE_MASK) < 0xFU);
    index = 0;
    UI_DrawSprite((s16)(task->pos.x + 144), (s16)(task->pos.y + 24), 0x16, 1);
    do {
        ability = index & BYTE_MASK;
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + 144), (s16)(task->pos.y + ((ability + 5) * 8)), 0x17, 1);
    } while ((index & BYTE_MASK) < 0xCU);
    index = 0;
    UI_DrawSprite((s16)(task->pos.x + 144), (s16)(task->pos.y + 136), 0x18, 1);
    UI_DrawSprite((s16)task->pos.x, (s16)(task->pos.y + 144), 0x19, 1);
    do {
        ability = index & BYTE_MASK;
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + ((ability + 1) * 8)), (s16)(task->pos.y + 144), 0x1A, 1);
    } while ((index & BYTE_MASK) < 9U);
    index = 0;
    UI_DrawSprite((s16)(task->pos.x + 80), (s16)(task->pos.y + 144), 0x1B, 1);
    do {
        ability = index & BYTE_MASK;
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + ((ability + 11) * 8)), (s16)(task->pos.y + 144), 0x1C, 1);
    } while ((index & BYTE_MASK) < 6U);
    UI_DrawSprite((s16)(task->pos.x + 136), (s16)(task->pos.y + 144), 0x1D, 1);
    func_801AFA1C(D_8014546C, task->unk_0A, (s16)(task->pos.x + 0x90), (s16)(task->pos.y + 0x18), 9, 0x80, 0x74);
}
#else
INCLUDE_ASM(func_801E112C);
#endif
