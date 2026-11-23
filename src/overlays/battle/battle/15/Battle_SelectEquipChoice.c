#include "battle_15.h"

/* func_80099830 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_SelectEquipChoice(void) {
    u16* pad_state;
    s32  buttons;
    u8   old_cursor;
    u8   item_id;
    u8   first_row;
    u8   last_row;
    u8   next;

    if (D_80148597 == 0) {
        D_801485DC = 1;
        D_801485E0 = D_80148598 + 7;
        D_801485E2 = D_8014859A + ((g_BattleListCursor - D_8014859E) * 13 + 26);
    } else {
        D_801485DC = 0;
    }
    pad_state = &g_PadStates[0].pressed;
    INPUT_REPEATED(*pad_state, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    buttons    = INPUT_REPEATED(*pad_state, (PADLup | PADLdown | PADL1 | PADR1));
    old_cursor = g_BattleListCursor;
    pad_state  = (u16*)&g_UiPanelTasks[17];
    if (buttons & PADLup) {
        if (old_cursor != 0) {
            g_BattleListCursor = old_cursor - 1;
        }
        if (g_BattleListCursor < D_8014859E) {
            D_801485A4 = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (old_cursor < 0x7F) {
            g_BattleListCursor = old_cursor + 1;
        }
        if (g_BattleListCursor >= D_8014859E + 7) {
            D_801485A4 = 0x10;
        }
    } else if (buttons & PADL1) {
        first_row = D_8014859E;
        if (first_row == 0) {
            g_BattleListCursor = 0;
        } else if (first_row < 7) {
            g_BattleListCursor = old_cursor - first_row;
            D_8014859E         = 0;
        } else {
            g_BattleListCursor = old_cursor - 7;
            D_8014859E         = first_row - 7;
        }
    } else if (buttons & PADR1) {
        last_row = D_8014859E;
        if (last_row == 0x79) {
            g_BattleListCursor = 0x7F;
        } else if (last_row >= 0x73) {
            next               = old_cursor + 0x79;
            g_BattleListCursor = next - last_row;
            D_8014859E         = 0x79;
        } else {
            g_BattleListCursor = old_cursor + 7;
            D_8014859E         = last_row + 7;
        }
    }
    if (old_cursor != FIELD(u8, pad_state, 0xBu)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    item_id                                         = D_801485A1;
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(Item_GetDescription((s32)D_8014859C, (s32)item_id) & 0xFFFF);
    pad_state                                       = &g_PadStates[0].pressed;
    if (*pad_state & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        goto equip_exit; /* cancel and a confirmed choice share the panel exit */
    }
    Battle_PreviewEquipment();
    if (*pad_state & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (item_id != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Battle_ApplyEquipment();
        equip_exit:
            g_BattleListCursor = 0xFF;
            D_801485C3         = 0xFF;
            D_801485C5         = 1;
            g_Battle.ui_mode -= 1;
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
    }
}
#else
INCLUDE_ASM(Battle_SelectEquipChoice);
#endif
