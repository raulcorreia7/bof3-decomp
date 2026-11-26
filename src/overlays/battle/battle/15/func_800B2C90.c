#include "battle_15.h"

/* Draws the ability panel: the ability icons of every row, their
 * names and the frame behind them.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800B2C90(MenuPanelTask* task) {
    FAKE_STACK_PADS(u8, 8);
    Ability* ability_obj;
    u8*      types;
    u8       scroll_y;
    u8       count;
    u8       ability_type;
    u8       ability_id;
    s16      line_y;
    u16      selection;
    u16      icon;
    s16      icon_x;
    s16      icon_y;
    u8       index;
    s32      has_icon;
    char*    text_table;
    void*    name_table;

    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 153, 130, 0, (s32)g_WindowStyle);
    selection = UI_ScrollList(&task->u.battle.cursor, &scroll_y, &count, &task->u.battle.row_base);
    selection &= BYTE_MASK;
    types  = Party_GetAbilities((u32)task->unk_0A, (u32)task->unk_0B, 1U) + selection;
    line_y = task->pos.y + (s8)scroll_y;
    if ((count + 7) != 0) {
        index = 0;
        do {
            if (*types != 0) {
                has_icon = (func_801AF5B0(task->unk_08, D_80148656, *types) & BYTE_MASK) == 0;
                icon     = (u16)(-has_icon & 7);
                if (index == task->flags) {
                    icon = 2;
                }
                ability_type = Char_AbilityGetCost(D_80148656, *types, 1U);
                ability_id   = (u8)(Char_AbilityGetElement((s32)*types));
                ability_obj  = &g_Abilities[*types];
                icon_x       = (s16)task->u.battle.cursor + index;
                if ((icon_x == task->flags) || (icon_x == task->unk_0C)) {
                    icon &= BYTE_MASK;
                    if (icon != 7) {
                        UI_ListDrawAbilityRow((s16)(task->pos.x + 7), (s16)(line_y + 0x1A), UI_TEXT_DIM, ability_id & BYTE_MASK, ability_obj, ability_type & BYTE_MASK, 1);
                    }
                    icon_y = (s16)(line_y + 0x18);
                } else {
                    icon_y = (s16)(line_y + 0x1A);
                }
                UI_ListDrawAbilityRow((s16)(task->pos.x + 7), icon_y, icon, ability_id & BYTE_MASK, ability_obj, ability_type & BYTE_MASK, 1);
            }
            index += 1;
            types += 1;
            line_y += 0xD;
        } while (index < count + 7);
    }
    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 153, 20, 0, (s32)g_WindowStyle);
    if ((s16)task->u.addr.unk_14 != 0) {
        text_table = (char*)&D_800B6ED4;
    } else {
        text_table = (char*)(&D_800B6EC4 + (task->unk_0B * 4));
    }
    selection = task->pos.x;
    selection += 0x4E;
    selection -= strlen(text_table) * 4;
    selection <<= 0x10;
    UI_TextDraw((s16)((s32)selection >> 16), (s16)(task->pos.y + 7), 0, MENU_LABEL_LENGTH, text_table);
    name_table = &s_BattleAbilityLine1Run;
    if (task->unk_09 & 2) {
        name_table = &s_BattleAbilityLine1FlagRun;
    }
    UI_SpriteDrawRun((s16)task->pos.x, (s16)task->pos.y, name_table, UI_SPRITE_ALT_PAGE);
    name_table = &s_BattleAbilityLine2Run;
    if (task->unk_09 & 1) {
        name_table = &s_BattleAbilityLine2FlagRun;
    }
    UI_SpriteDrawRun((s16)task->pos.x, (s16)task->pos.y, name_table, UI_SPRITE_ALT_PAGE);
    ability_type = task->unk_09;
    if (!(ability_type & 0xF0)) {
        task->unk_09 = 0;
    } else {
        task->unk_09 = ability_type - 0x10;
    }
    index = 0;
    do {
        selection = index;
        index += 1;
        UI_SpriteDraw((s16)(task->pos.x + ((selection + 5) * 8)), (s16)task->pos.y, 1, UI_SPRITE_ALT_PAGE);
    } while (index < 10);
    index = 0;
    do {
        selection = index;
        index += 1;
        UI_SpriteDraw((s16)task->pos.x, (s16)(task->pos.y + ((selection + 3) * 8)), 4, UI_SPRITE_ALT_PAGE);
    } while (index < 12);
    index = 0;
    UI_SpriteDraw((s16)(task->pos.x + 144), (s16)(task->pos.y + 24), 0x16, UI_SPRITE_ALT_PAGE);
    do {
        selection = index;
        index += 1;
        UI_SpriteDraw((s16)(task->pos.x + 144), (s16)(task->pos.y + ((selection + 5) * 8)), 0x17, UI_SPRITE_ALT_PAGE);
    } while (index < 9);
    index = 0;
    UI_SpriteDraw((s16)(task->pos.x + 144), (s16)(task->pos.y + 112), 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)task->pos.x, (s16)(task->pos.y + 120), 0x19, UI_SPRITE_ALT_PAGE);
    do {
        selection = index;
        index += 1;
        UI_SpriteDraw((s16)(task->pos.x + ((selection + 1) * 8)), (s16)(task->pos.y + 120), 0x1A, UI_SPRITE_ALT_PAGE);
    } while (index < 17);
    if ((s16)task->u.addr.unk_14 != 0) {
        UI_SpriteDraw((s16)(task->pos.x + 8), (s16)task->pos.y, 0x32, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw((s16)(task->pos.x + 144), (s16)task->pos.y, 0x33, UI_SPRITE_ALT_PAGE);
    }
    UI_ListDrawScrollbar(Party_GetAbilities((u32)task->unk_0A, (u32)task->unk_0B, 1U), (u8)task->u.battle.cursor, (s16)(task->pos.x + 0x90), (s16)(task->pos.y + 0x18), 7, 0xA, 0x5C);
}
#else
INCLUDE_ASM(func_800B2C90);
#endif
