#include "battle_03.h"

MATCH void func_801DDFEC(u32 battler_index) {
    u32 index;
    u32 battler;
    u32 substate;

    if ((battler_index & BYTE_MASK) >= 3u) {
        return;
    }
    index = D_80146322 - 1u;
    /* enter the scan at its bound test */
    goto check;
    for (;;) {
    body:
        battler = *(u8*)((char*)&D_8014630C + (index & BYTE_MASK));
        if (battler == (battler_index & BYTE_MASK)) {
            if (g_BattlePartyBattlers[battler].command.type != 5u) {
                return;
            }
            substate = g_BattlePartyBattlers[battler].command.id;
            if ((substate >> 8) != 0u) {
                return;
            }
            func_801DDE7C(g_BattlePartyBattlers[battler].unk_122, substate);
            return;
        }
        index += 1u;
    check:
        if ((index & BYTE_MASK) < D_80146323) {
            /* next ranked owner */
            goto body;
        }
        return;
    }
}
