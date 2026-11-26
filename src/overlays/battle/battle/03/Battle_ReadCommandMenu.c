#include "battle_03.h"

/* func_801D1E8C */
#ifdef NON_MATCHING
NON_MATCHING void Battle_ReadCommandMenu(void) {
    PartyMember* temp_v0_66;
    s32          temp_v1_80;
    s8           temp_v0_50;
    s8           i;

    if (g_Battle.selection != 0) {
        g_Battle.selection--;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) && ((s8)g_Battle.command_count != 0)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_Battle.phase.step -= 1;
        temp_v0_50             = (u8)g_Battle.command_count - 1;
        g_Battle.command_count = temp_v0_50;
        temp_v0_66              = &g_Game.members[D_801462F6[temp_v0_50]];
        g_BattleMessageSlot     = &temp_v0_66->header.flags;
        temp_v0_66->header.mode = 2;
        temp_v0_66->u.turn.action_flags.value &= ~BATTLER_ACTION_ABILITY_ALT_POSE;
        if (FIELD(u8, g_BattleMessageSlot, 0x119u) == 5) {
            temp_v1_80 = FIELD(s32, g_BattleMessageSlot, 0x124u);
            if (!(temp_v1_80 & 0x4000)) {
                func_801DDE7C((u32)FIELD(u8, g_BattleMessageSlot, 0x122u), (u32)FIELD(u16, g_BattleMessageSlot, 0x11Au));
            } else {
                FIELD(s32, g_BattleMessageSlot, 0x124u) = (s32)(temp_v1_80 & ~0x4000);
            }
        }
        FIELD(s32, g_BattleMessageSlot, 0x124u) = 0;
        FIELD(u8, g_BattleMessageSlot, 0x119u)  = 0U;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (((u32)(g_Battle.panel_slot - 2) < 2U) && (g_BattleActorTurn->action_flags.value & BATTLER_ACTION_DRAGON_FORM)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_UiPanelTasks[3].state          = 2;
        *(u8*)(&g_UiPanelTasks[2].state) = 2;
        g_Battle.phase.step += 2;
        g_Battle.phase.sub_step = g_Battle.panel_slot;
        return;
    }
    if (g_PadStates[0].held & PADselect) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        *(u8*)(&g_UiPanelTasks[2].state) = 2;
        g_UiPanelTasks[1].state          = 2;
        g_UiPanelTasks[3].state          = 2;
        Battle_DrawPanels(D_8014837C, D_8014837E);
        func_801D8450((u32)g_Battle.panel_slot);
        Battle_DrawPartyPanel((s32)D_80148358, (s32)D_8014835A);
        g_Battle.phase.step += 1;
        return;
    }
    if (g_PadStates[0].held & (INPUT_DIRECTIONAL | PADL1 | PADR1)) {
        for (i = 5; i >= 0; i--) {
            if (g_PadStates[0].held & D_801EABCC[i]) {
                if (g_PadStates[0].pressed & D_801EABCC[i]) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
                    if (g_Battle.cursor.panel_entry == i + 1) {
                        if (g_Battle.selection != 0) {
                            if ((u8)(i - 1) < 2 && (g_BattleActorTurn->action_flags.value & BATTLER_ACTION_DRAGON_FORM)) {
                                g_Battle.selection          = 0;
                                g_Battle.cursor.panel_entry = 0;
                                return;
                            }
                            g_Battle.phase.step += 2;
                            g_Battle.panel_slot              = i + 1;
                            g_Battle.phase.sub_step          = i + 1;
                            *(u8*)(&g_UiPanelTasks[2].state) = 2;
                            g_UiPanelTasks[3].state          = 2;
                            g_Battle.selection               = 0;
                            g_Battle.cursor.panel_entry      = 0;
                            return;
                        }
                    }
                    g_Battle.selection          = 8;
                    g_Battle.cursor.panel_entry = i + 1;
                }
                g_Battle.panel_slot = i + 1;
            }
        }
        return;
    }
    if (g_Battle.panel_slot != 0) {
        g_Battle.panel_slot = 0;
    }
}
#else
INCLUDE_ASM(Battle_ReadCommandMenu);
#endif
