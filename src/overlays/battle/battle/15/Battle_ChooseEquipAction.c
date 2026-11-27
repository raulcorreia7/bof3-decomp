#include "battle_15.h"

/* func_80099364 */
MATCH void Battle_ChooseEquipAction(void) {
    u8* option;
    u8* choice;
    u8  mode;

    option                                        = &g_UIPanelTasks[21].unk_0A;
    g_BattleMessages[(D_801EC328 - 1) & 0xF].text = UI_MessageGetText(*option == 0 ? 0x2F : 0x31);
    if (g_UIPanelTasks[21].state == 0) {
        g_UIPanelTasks[19].active = 1;
        g_UIPanelTasks[19].pos.vx = g_UIPanelTasks[21].pos.vx + *option * 48;
        g_UIPanelTasks[19].pos.vy = g_UIPanelTasks[21].pos.vy + 4;
    } else {
        g_UIPanelTasks[19].active = 0;
    }
    choice  = &g_UIPanelTasks[21].unk_0B;
    *choice = 0xFF;
    if ((g_PadStates[0].pressed & (PADLleft | PADLright)) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UIPanelTasks[21].unk_0A ^= 1;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0) {
        g_UIPanelTasks[21].active = 0;
        g_UIPanelTasks[4].active  = 1;
        g_Battle.phase.sub_step   = 2;
        g_Battle.ui_step          = 1;
    } else if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        *choice = g_UIPanelTasks[21].unk_0A;
        if (g_UIPanelTasks[21].unk_0A == 0) {
            Battle_InitEquipUsePanel();
            g_Battle.ui_mode += 3;
        } else {
            Battle_InitEquipChangePanel();
            mode                      = g_Battle.ui_mode;
            g_UIPanelTasks[17].unk_09 = g_BattleEquipSlot;
            g_UIPanelTasks[17].unk_0C = g_UIPanelTasks[18].unk_0C;
            g_Battle.ui_mode          = mode + 1;
        }
    } else if ((g_PadStates[0].pressed & PADLdown) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UIPanelTasks[21].active = 0;
        g_UIPanelTasks[4].active  = 1;
        g_Battle.phase.sub_step   = 2;
        g_Battle.ui_step          = 1;
    }
}
