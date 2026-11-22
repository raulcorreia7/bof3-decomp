#include "battle_15.h"

/* func_80099364 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_ChooseEquipAction(void) {
    u8* state;
    u8* panel;

    state                                           = &D_8014862E;
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText((*state) == 0u ? 0x2Fu : 0x31u);
    if (D_80148627 == 0u) {
        D_801485DC = 1u;
        D_801485E0 = D_80148628 + (*state * 0x30);
        D_801485E2 = D_8014862A + 4u;
    } else {
        D_801485DC = 0u;
    }
    panel  = &D_8014862F;
    *panel = 0xFFu;
    if ((g_PadStates[0].pressed & (PADLleft | PADLright)) != 0u) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        D_8014862E ^= 1u;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_UiPanelTasks[21].active = 0u;
        g_UiPanelTasks[4].active  = 1u;
        g_Battle.phase.sub_step   = 2u;
        g_Battle.ui_step          = 1u;
    } else if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        *panel = D_8014862E;
        if (D_8014862E == 0u) {
            Battle_InitEquipUsePanel();
            g_Battle.ui_mode += 3u;
        } else {
            Battle_InitEquipChangePanel();
            g_UiPanelTasks[17].unk_09 = g_BattleEquipSlot;
            g_UiPanelTasks[17].unk_0C = g_UiPanelTasks[18].unk_0C;
            g_Battle.ui_mode += 1u;
        }
    } else if ((g_PadStates[0].pressed & PADLdown) != 0u) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[21].active = 0u;
        g_UiPanelTasks[4].active  = 1u;
        g_Battle.phase.sub_step   = 2u;
        g_Battle.ui_step          = 1u;
    }
}
#else
INCLUDE_ASM(Battle_ChooseEquipAction);
#endif
