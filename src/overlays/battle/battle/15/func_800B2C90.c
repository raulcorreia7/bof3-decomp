#include "battle_15.h"

/* Draws the ability panel: the ability icons of every row, their
 * names and the frame behind them.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800B2C90(MenuPanelTask* task) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    Ability* ability_obj;
    u8*      kinds;
    u8       row_offset;
    u8       count;
    u8       ability_kind;
    u8       ability_id;
    u16      row_y;
    u16      selection;
    u16      icon;
    s16      icon_x;
    s16      icon_y;
    s32      index;
    s32      has_icon;
    char*    text_table;
    void*    name_table;

    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 153, 130, 0, (s32)g_WindowStyle);
    selection = func_801AFD10(&task->u.battle.cursor, &row_offset, &count, &task->u.battle.row_base);
    selection &= BYTE_MASK;
    kinds = Party_GetAbilities((u32)task->unk_0A, (u32)task->unk_0B, 1U) + selection;
    row_y = task->pos.y + (s8)row_offset;
    if ((count + 7) != 0) {
        index = 0;
        do {
            if (*kinds != 0) {
                has_icon = (func_801AF5B0(task->unk_08, D_80148656, *kinds) & BYTE_MASK) == 0;
                icon     = (u16)(-has_icon & 7);
                if ((index & BYTE_MASK) == task->flags) {
                    icon = 2;
                }
                ability_kind = Char_GetAbilityCost(D_80148656, *kinds, 1U);
                ability_id   = (u8)(Char_GetAbilityElement((s32)*kinds));
                ability_obj  = &g_Abilities[*kinds];
                icon_x       = (s16)task->u.battle.cursor + (index & BYTE_MASK);
                if ((icon_x == task->flags) || (icon_x == task->unk_0C)) {
                    icon &= BYTE_MASK;
                    if (icon != 7) {
                        func_801AF930((s16)(task->pos.x + 7), (s16)(row_y + 0x1A), 7U, ability_id & BYTE_MASK,
                                      ability_obj, ability_kind & BYTE_MASK, 1);
                    }
                    icon_y = (s16)(row_y + 0x18);
                } else {
                    icon_y = (s16)(row_y + 0x1A);
                }
                func_801AF930((s16)(task->pos.x + 7), icon_y, icon, ability_id & BYTE_MASK, ability_obj,
                              ability_kind & BYTE_MASK, 1);
            }
            index += 1;
            kinds += 1;
            row_y += 0xD;
        } while ((index & BYTE_MASK) < (count + 7));
    }
    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 153, 20, 0, (s32)g_WindowStyle);
    if ((s16)task->u.addr.unk_14 != 0) {
        text_table = (char*)&D_800B6ED4;
    } else {
        text_table = (char*)(&D_800B6EC4 + (task->unk_0B * 4));
    }
    selection = task->pos.x;
    selection += 0x4E;
    selection -= strlen(text_table) * 4;
    selection <<= 0x10;
    UI_DrawText((s16)((s32)selection >> 16), (s16)(task->pos.y + 7), 0, 0x10U, text_table);
    name_table = &s_BattleAbilityLine1Run;
    if (task->unk_09 & 2) {
        name_table = &s_BattleAbilityLine1FlagRun;
    }
    UI_DrawSpriteRun((s16)task->pos.x, (s16)task->pos.y, name_table, 1);
    name_table = &s_BattleAbilityLine2Run;
    if (task->unk_09 & 1) {
        name_table = &s_BattleAbilityLine2FlagRun;
    }
    UI_DrawSpriteRun((s16)task->pos.x, (s16)task->pos.y, name_table, 1);
    ability_kind = task->unk_09;
    if (!(ability_kind & 0xF0)) {
        task->unk_09 = 0;
    } else {
        task->unk_09 = ability_kind - 0x10;
    }
    index = 0;
    do {
        selection = (u16)(index & BYTE_MASK);
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + ((selection + 5) * 8)), (s16)task->pos.y, 1, 1);
    } while ((index & BYTE_MASK) < 0xAU);
    index = 0;
    do {
        selection = (u16)(index & BYTE_MASK);
        index += 1;
        UI_DrawSprite((s16)task->pos.x, (s16)(task->pos.y + ((selection + 3) * 8)), 4, 1);
    } while ((index & BYTE_MASK) < 0xCU);
    index = 0;
    UI_DrawSprite((s16)(task->pos.x + 144), (s16)(task->pos.y + 24), 0x16, 1);
    do {
        selection = (u16)(index & BYTE_MASK);
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + 144), (s16)(task->pos.y + ((selection + 5) * 8)), 0x17, 1);
    } while ((index & BYTE_MASK) < 9U);
    index = 0;
    UI_DrawSprite((s16)(task->pos.x + 144), (s16)(task->pos.y + 112), 0x18, 1);
    UI_DrawSprite((s16)task->pos.x, (s16)(task->pos.y + 120), 0x19, 1);
    do {
        selection = (u16)(index & BYTE_MASK);
        index += 1;
        UI_DrawSprite((s16)(task->pos.x + ((selection + 1) * 8)), (s16)(task->pos.y + 120), 0x1A, 1);
    } while ((index & BYTE_MASK) < 0x11U);
    if ((s16)task->u.addr.unk_14 != 0) {
        UI_DrawSprite((s16)(task->pos.x + 8), (s16)task->pos.y, 0x32, 1);
        UI_DrawSprite((s16)(task->pos.x + 144), (s16)task->pos.y, 0x33, 1);
    }
    func_801AFA1C(Party_GetAbilities((u32)task->unk_0A, (u32)task->unk_0B, 1U), (u8)task->u.battle.cursor,
                  (s16)(task->pos.x + 0x90), (s16)(task->pos.y + 0x18), 7, 0xA, 0x5C);
}
#else
INCLUDE_ASM(func_800B2C90);
#endif
