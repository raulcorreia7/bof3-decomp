#include "battle_03.h"

/* waits until the sixteen hand-off markers g_SndVoiceStatus[16..23] are clear, then either performs the
 * configured reset or reinitialises the panel rows, stream slot and first three battler slots and clears the battle
 * bits.
 */
/* func_801D656C */
MATCH void Battle_WaitVoiceSlots(void) {
    u8 i;

    for (i = 16; i < 24; i++) {
        if (g_SndVoiceStatus[i] != 0) {
            return;
        }
    }
    if (BATTLE_IS_SCRIPTED() && g_Battle.boss_event_hook(BOSS_EVENT_TURN_END) == BOSS_EVENT_PENDING) {
        return;
    }
    if (g_Battle.outcome.result != 0) {
        g_UIPanelTasks[1].active  = 0;
        g_UIPanelTasks[4].active  = 0;
        D_80148378[0]             = 0;
        g_UIPanelTasks[12].active = 0;
        g_UIPanelTasks[11].active = 0;
        g_UIPanelTasks[10].active = 0;
        g_UIPanelTasks[9].active  = 0;
        g_UIPanelTasks[8].active  = 0;
        g_UIPanelTasks[7].active  = 0;
        g_UIPanelTasks[6].active  = 0;
        g_UIPanelTasks[5].active  = 0;
        g_Battle.phase.mode       = BATTLE_MODE_RESULT;
        g_Battle.phase.step       = 0;
        g_Battle.flags &= ~BATTLE_STATE_COMMAND_ARMED;
    } else {
        if (!(g_Battle.flags & BATTLE_STATE_COMMAND_ARMED)) {
            for (i = 1; i < 7; i++) {
                g_Battle.panel_widths[i] = 0;
            }
            g_Battle.panel_widths[0] = 8;
            g_Battle.panel_slot      = 0;
            EMI_ArchiveLoad(EMI_SLOT_COMN_SE);
        }
        func_801DB494();
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                g_Game.members[i].header.mode = 2;
            }
        }
        g_Battle.outcome.surprise = 0;
        g_Battle.phase.mode       = BATTLE_MODE_COMMANDS;
        g_Battle.phase.step       = 0;
        g_Battle.phase.sub_step   = 0;
        g_Battle.flags &= 0xFFF7;
    }
}
