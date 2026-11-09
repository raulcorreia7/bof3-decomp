#include "battle_03.h"

/* stages the battle script record selected by the active battler's status flags and action state
 * into the battle script table, or arms the record already staged.
 */
MATCH void func_801DEFE4(void) {
    PartyMember* work;
    PartyMember* battler;
    u16          flags;
    u8           state;

    if (g_Battle.outcome.options & 0x20) {
        if ((g_Battle.phase.mode == BATTLE_MODE_RESULT) && BATTLE_IS_VICTORY()) {
            if (HAS_STATUS(*g_Game.current, STATUS_KO)) {
                Actor_SwitchScript(g_Task->facing + 0x1C, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0x1800);
            } else {
                Actor_SwitchScript(g_Task->unk_4B, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0x1800);
            }
            return;
        }
    } else if ((g_Battle.phase.mode == BATTLE_MODE_RESULT) && BATTLE_IS_VICTORY()) {
        if (HAS_STATUS(*g_Game.current, STATUS_KO)) {
            Actor_SwitchScript(g_Task->facing + 0x1C, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0x1800);
        } else {
            Actor_SwitchScript(g_Task->facing + 0x20, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0x1800);
        }
        return;
    }

    work  = g_Game.current;
    flags = work->chr.status;
    if (flags & STATUS_KO) {
        Actor_RequestScript(g_Task->facing + 0x1C);
        return;
    }
    if (flags & 0x800) {
        Actor_RequestScript(g_Task->facing + 0x30);
        return;
    }
    if (g_Battle.state & BATTLE_STATE_COMMAND_ARMED) {
        if (flags & STATUS_PARALYZED) {
            Actor_RequestScript(g_Task->facing + 0x4);
            return;
        }
        if (flags & 0x20C0) {
            Actor_RequestScript(g_Task->facing + 0x18);
        } else {
            Actor_RequestScript(g_Task->facing + 0x8);
        }
        return;
    }
    if (work->u.turn.damage_flags.value & COMBATANT_FLAG_DEFENDING) {
        Actor_RequestScript(g_Task->facing + 0x14);
        return;
    }

    state = work->u.turn.command.type;
    switch (state) {
        case 0:
            if (HAS_STATUS(*g_Game.current, 0x20C0)) {
                Actor_RequestScript(g_Task->facing + 0x18);
            } else {
                Actor_RequestScript(g_Task->facing + 0x4);
            }
            return;
        case 1:
            Actor_RequestScript(g_Task->facing + 0x8);
            return;
        case 2:
            Actor_RequestScript(g_Task->facing + 0x14);
            return;
        case 4:
            battler = g_Game.current;
            if (battler->u.turn.action_flags.value & COMBATANT_FLAG_ABILITY_ALT_POSE) {
                Actor_RequestScript(g_Task->facing + 0x38);
            } else if (D_801CA71C[battler->u.turn.command.id].mask & 0x800) {
                Actor_RequestScript(g_Task->facing + 0x8);
            } else {
                Actor_RequestScript(g_Task->facing + 0x28);
            }
            return;
        case 5:
            Actor_RequestScript(g_Task->facing + 0x4);
            return;
        default:
            return;
    }
}
