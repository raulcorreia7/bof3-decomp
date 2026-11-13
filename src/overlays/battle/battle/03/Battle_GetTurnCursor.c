#include "battle_03.h"

/* func_801DDFEC */
MATCH void Battle_GetTurnCursor(u32 battler_index) {
    u32 index;
    u32 battler;
    u32 substate;

    if ((battler_index & BYTE_MASK) >= 3u) {
        return;
    }
    index = g_Battle.turn_cursor - 1u;
    /* enter the scan at its bound test */
    goto check;
    for (;;) {
    body:
        battler = g_Battle.turn_order[index & BYTE_MASK];
        if (battler == (battler_index & BYTE_MASK)) {
            if (g_Game.members[battler].u.turn.command.type != BATTLE_COMMAND_ITEM) {
                return;
            }
            substate = g_Game.members[battler].u.turn.command.id;
            if ((substate >> 8) != 0u) {
                return;
            }
            func_801DDE7C(g_Game.members[battler].u.turn.choice, substate);
            return;
        }
        index += 1u;
    check:
        if ((index & BYTE_MASK) < g_Battle.turn_count) {
            /* next ranked owner */
            goto body;
        }
        return;
    }
}
