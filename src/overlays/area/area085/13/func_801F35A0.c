#include "area085_13.h"

MATCH void func_801F35A0(void) {
    PartyBattler* battler;
    PartyBattler* battler2;

    if (g_Task->timer != 0) {
        battler = &D_801469B8;
        if (g_Task->param.unk_0B != 0) {
            battler = g_BattlePartyBattlers;
        }
        battler->header.flags |= PARTY_BATTLER_FLAG_HANDLER_BUSY;
        g_Task->timer -= 1;
        return;
    }
    battler2 = &D_801469B8;
    if (g_Task->param.unk_0B != 0) {
        battler2 = g_BattlePartyBattlers;
    }
    battler2->header.flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
    g_Actors[g_Task->unk_03].header.flags = 0;
    g_Actors[g_Task->unk_04].header.flags = 0;
    g_Task->header.mode                   = 2;
}
