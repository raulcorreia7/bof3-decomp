#include "battle_15.h"

MATCH void func_8009761C(void) {
    u8* entry;
    u8  flags;

    entry = Party_GetAbilities(D_80148656, D_8014857B, 1);
    flags = D_801CA718[entry[D_8014857C] * 0x14];
    if ((flags & 0x40u) != 0u) {
        if ((flags & 0x10u) != 0u) {
            g_BattleUIStep = 5u;
        } else {
            g_BattleUIStep = 4u;
        }
        return;
    }
    if ((flags & 0x80u) != 0u) {
        D_801EB4D8->command.target = 0xC0u;
    } else if ((flags & 0x10u) != 0u) {
        if ((flags & 0x20u) != 0u) {
            D_801EB4D8->command.target = 0x40u;
        } else {
            D_801EB4D8->command.target = 0x80u;
        }
    } else {
        D_801EB4D8->command.target = g_BattleMessageSlot[5];
    }
    g_BattleUIStep  = 4u;
    g_BattleUIState = 3u;
}
