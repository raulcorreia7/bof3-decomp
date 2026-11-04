#include "area085_13.h"

MATCH void func_801F35A0(void) {
    PartyBattler* var_v1;
    PartyBattler* var_v1_2;

    if (g_SpadWork->unk_09 != 0) {
        var_v1 = &D_801469B8;
        if (g_SpadWork->unk_0B != 0) {
            var_v1 = g_BattlePartyBattlers;
        }
        var_v1->flags_00 |= 0x40;
        g_SpadWork->unk_09 -= 1;
        return;
    }
    var_v1_2 = &D_801469B8;
    if (g_SpadWork->unk_0B != 0) {
        var_v1_2 = g_BattlePartyBattlers;
    }
    var_v1_2->flags_00 &= 0xBF;
    g_Actors[g_SpadWork->unk_03].flags_00 = 0;
    g_Actors[g_SpadWork->unk_04].flags_00 = 0;
    g_SpadWork->unk_01                    = 2;
}
