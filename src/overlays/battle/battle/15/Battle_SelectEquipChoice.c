#include "battle_15.h"

void Battle_ApplyEquipment(void); /* extern */

/* func_80099830 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_SelectEquipChoice(void) {
    u16* pad_state;
    s32  pad;
    u32  scroll_lo;
    u32  scroll_hi;
    u8   choice;
    u8   new_scroll;

    if (D_80148597 == 0) {
        D_801485DC = 1;
        D_801485E0 = D_80148598 + 7;
        D_801485E2 = D_8014859A + (((g_BattleListCursor - g_UiPanelTasks[17].unk_0A) * 0xD) + 0x1A);
    } else {
        D_801485DC = 0;
    }
    pad_state = &g_PadStates[0].pressed;
    INPUT_REPEATED(*pad_state, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    pad       = INPUT_REPEATED(*pad_state, (PADLup | PADLdown | PADL1 | PADR1));
    pad_state = (u16*)&D_80148594;
    if (pad & PADLup) {
        if (g_BattleListCursor != 0) {
            g_BattleListCursor -= 1;
        }
        if ((u8)g_BattleListCursor < (u8)g_UiPanelTasks[17].unk_0A) {
            g_UiPanelTasks[17].u.grow.w = 0xF0;
        }
    } else if (pad & PADLdown) {
        if ((u8)g_BattleListCursor < 0x7FU) {
            g_BattleListCursor += 1;
        }
        if ((s32)g_BattleListCursor >= (g_UiPanelTasks[17].unk_0A + 7)) {
            g_UiPanelTasks[17].u.grow.w = 0x10;
        }
    } else if (pad & 4) {
        scroll_lo = g_UiPanelTasks[17].unk_0A & BYTE_MASK;
        if (scroll_lo == 0) {
            g_BattleListCursor = 0;
        } else if (scroll_lo < 7U) {
            g_BattleListCursor -= g_UiPanelTasks[17].unk_0A;
            g_UiPanelTasks[17].unk_0A = 0;
        } else {
            g_BattleListCursor -= 7;
            new_scroll = g_UiPanelTasks[17].unk_0A - 7;
            goto block_25; /* shared scroll/confirm join */
        }
    } else if (pad & 8) {
        scroll_hi = g_UiPanelTasks[17].unk_0A & BYTE_MASK;
        if (scroll_hi == 0x79) {
            g_BattleListCursor = 0x7F;
        } else {
            if (scroll_hi >= 0x73U) {
                g_BattleListCursor = (g_BattleListCursor + 0x79) - g_UiPanelTasks[17].unk_0A;
                new_scroll         = 0x79;
            } else {
                g_BattleListCursor += 7;
                new_scroll = g_UiPanelTasks[17].unk_0A + 7;
            }
        block_25:
            g_UiPanelTasks[17].unk_0A = new_scroll;
        }
    }
    if (g_BattleListCursor != FIELD(u8, pad_state, 0xBu)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    choice                                          = g_UiPanelTasks[17].flags;
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(Item_GetDescription((s32)g_UiPanelTasks[17].unk_08, (s32)choice) & HALF_MASK);
    pad_state                                       = &g_PadStates[0].pressed;
    if (g_InputMasks[BATTLE_INPUT_CANCEL] & *pad_state) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        goto block_33; /* shared scroll/confirm join */
    }
    Battle_PreviewEquipment();
    if (g_InputMasks[BATTLE_INPUT_CONFIRM] & *pad_state) {
        if (choice != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Battle_ApplyEquipment();
        block_33:
            g_BattleListCursor        = 0xFF;
            g_UiPanelTasks[18].unk_0B = 0xFF;
            D_801485C5                = 1;
            g_Battle.ui_mode -= 1;
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
    }
}
#else
INCLUDE_ASM(Battle_SelectEquipChoice);
#endif
