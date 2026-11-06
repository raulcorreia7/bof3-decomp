#include "battle_03.h"

MATCH void func_801DDFEC(u32 battler_index) {
    u32 index;
    u32 battler;
    u32 substate;

    if ((battler_index & 0xFF) >= 3u) {
        return;
    }
    index = D_80146322 - 1u;
    /* enter the scan at its bound test */
    goto check;
    for (;;) {
    body:
        battler = *(u8*)((char*)&D_8014630C + (index & 0xFF));
        if (battler == (battler_index & 0xFF)) {
            if (g_BattlePartyBattlers[battler].turn.command.type != BATTLE_COMMAND_ITEM) {
                return;
            }
            substate = g_BattlePartyBattlers[battler].turn.command.id;
            if ((substate >> 8) != 0u) {
                return;
            }
            func_801DDE7C(g_BattlePartyBattlers[battler].turn.choice, substate);
            return;
        }
        index += 1u;
    check:
        if ((index & 0xFF) < D_80146323) {
            /* next ranked owner */
            goto body;
        }
        return;
    }
}
