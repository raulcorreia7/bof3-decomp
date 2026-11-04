#include "area085_13.h"

MATCH void func_801F35A0(void) {
    PartyBattler* battler;
    PartyBattler* battler2;

    if (g_SpadWork->unk_09 != 0) {
        battler = &D_801469B8;
        if (g_SpadWork->unk_0B != 0) {
            battler = g_BattlePartyBattlers;
        }
        battler->flags_00 |= 0x40;
        g_SpadWork->unk_09 -= 1;
        return;
    }
    battler2 = &D_801469B8;
    if (g_SpadWork->unk_0B != 0) {
        battler2 = g_BattlePartyBattlers;
    }
    battler2->flags_00 &= 0xBF;
    g_Actors[g_SpadWork->unk_03].flags_00 = 0;
    g_Actors[g_SpadWork->unk_04].flags_00 = 0;
    g_SpadWork->unk_01                    = 2;
}
