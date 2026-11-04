#include "battle_03.h"

/* stages the battle script record selected by the active battler's status flags and action state
 * into the battle script bank, or arms the record already staged.
 */
MATCH void func_801DEFE4(void) {
    PartyBattler* work;
    PartyBattler* battler;
    u16           flags;
    u8            state;

    if (g_BattleOptions & 0x20) {
        if ((g_BattleMode == 5) && BATTLE_IS_VICTORY()) {
            if (HAS_STATUS(*g_GameState, STATUS_KO)) {
                Actor_SwitchScript(g_SpadWork->word_08.byte.facing_08 + 0x1C, (u8*)0x800F0800U, 0x1800);
            } else {
                Actor_SwitchScript(g_SpadWork->unk_4B, (u8*)0x800F0800U, 0x1800);
            }
            return;
        }
    } else if ((g_BattleMode == 5) && BATTLE_IS_VICTORY()) {
        if (HAS_STATUS(*g_GameState, STATUS_KO)) {
            Actor_SwitchScript(g_SpadWork->word_08.byte.facing_08 + 0x1C, (u8*)0x800F0800U, 0x1800);
        } else {
            Actor_SwitchScript(g_SpadWork->word_08.byte.facing_08 + 0x20, (u8*)0x800F0800U, 0x1800);
        }
        return;
    }

    work  = g_GameState;
    flags = work->stats.status;
    if (flags & STATUS_KO) {
        Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x1C);
        return;
    }
    if (flags & 0x800) {
        Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x30);
        return;
    }
    if (g_BattleState & BATTLE_STATE_COMMAND_ARMED) {
        if (flags & STATUS_PARALYZED) {
            Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x4);
            return;
        }
        if (flags & 0x20C0) {
            Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x18);
        } else {
            Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x8);
        }
        return;
    }
    if (work->flags_124.value & 2) {
        Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x14);
        return;
    }

    state = work->mode_119;
    switch (state) {
        case 0:
            if (HAS_STATUS(*g_GameState, 0x20C0)) {
                Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x18);
            } else {
                Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x4);
            }
            return;
        case 1:
            Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x8);
            return;
        case 2:
            Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x14);
            return;
        case 4:
            battler = g_GameState;
            if (battler->flags_128.value & 4) {
                Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x38);
            } else if (D_801CA71C[battler->command].mask & 0x800) {
                Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x8);
            } else {
                Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x28);
            }
            return;
        case 5:
            Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x4);
            return;
        default:
            return;
    }
}
