#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    func_8014D978();
    if (EMI_LoaderIsReady() != 0) {
        Battle_DefeatEnemy();
        ((PartyBattler*)g_Task)->flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        ((PartyBattler*)g_Task)->mode   = 6;
        ((PartyBattler*)g_Task)->step   = 4;
        ((PartyBattler*)g_Task)->unk_03 = 6;
    }
}
