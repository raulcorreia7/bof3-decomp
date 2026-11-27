#include "battle_03.h"

/* func_801D1E8C */
/* Reads the pad on the command menu: cancel steps back to the previous member's command,
 * confirm or a second press of the same entry opens it, select opens the party panels. */
MATCH void Battle_ReadCommandMenu(void) {
    PartyMember* member;
    u32          damage_flags;
    s8           count;
    s8           i;

    if (g_Battle.selection != 0) {
        g_Battle.selection--;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) && ((s8)g_Battle.command_count != 0)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_Battle.phase.step -= 1;
        count                  = g_Battle.command_count - 1;
        g_Battle.command_count = count;
        member                 = &g_Game.members[D_801462F6[count]];
        g_BattleMessageSlot    = &member->header.flags;
        member->header.mode    = 2;
        member->u.turn.action_flags.value &= ~BATTLER_ACTION_ABILITY_ALT_POSE;
        if (((PartyMember*)g_BattleMessageSlot)->u.turn.command.type == BATTLE_COMMAND_ITEM) {
            damage_flags = ((PartyMember*)g_BattleMessageSlot)->u.turn.damage_flags.value;
            if (!(damage_flags & 0x4000)) {
                func_801DDE7C(((PartyMember*)g_BattleMessageSlot)->u.turn.choice, ((PartyMember*)g_BattleMessageSlot)->u.turn.command.id);
            } else {
                ((PartyMember*)g_BattleMessageSlot)->u.turn.damage_flags.value = damage_flags & ~0x4000;
            }
        }
        ((PartyMember*)g_BattleMessageSlot)->u.turn.damage_flags.value = 0;
        ((PartyMember*)g_BattleMessageSlot)->u.turn.command.type       = 0;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (((u32)(g_Battle.panel_slot - 2) < 2U) && (g_BattleActorTurn->action_flags.value & BATTLER_ACTION_DRAGON_FORM)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_UiPanelTasks[3].state = 2;
        g_UiPanelTasks[2].state = 2;
        g_Battle.phase.step += 2;
        g_Battle.phase.sub_step = g_Battle.panel_slot;
        return;
    }
    if (g_PadStates[0].held & PADselect) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_UiPanelTasks[2].state = 2;
        g_UiPanelTasks[1].state = 2;
        g_UiPanelTasks[3].state = 2;
        Battle_DrawPanels(g_UiPanelTasks[2].pos.vx, g_UiPanelTasks[2].pos.vy);
        func_801D8450((u32)g_Battle.panel_slot);
        Battle_DrawPartyPanel((s32)g_UiPanelTasks[1].pos.vx, (s32)g_UiPanelTasks[1].pos.vy);
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
                            g_UiPanelTasks[2].state = g_UiPanelTasks[3].state = 2;
                            g_Battle.phase.step += 2;
                            g_Battle.phase.sub_step = g_Battle.panel_slot = i + 1;
                            g_Battle.selection                            = 0;
                            g_Battle.cursor.panel_entry                   = 0;
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
