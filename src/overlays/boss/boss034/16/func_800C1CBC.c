#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    func_8014D978();
    if (EMI_LoaderIsReady() != 0) {
        Battle_DefeatEnemy();
        ((PartyBattler*)g_Task)->header.flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        ((PartyBattler*)g_Task)->header.mode = 6;
        ((PartyBattler*)g_Task)->header.step = 4;
        ((PartyBattler*)g_Task)->unk_03      = 6;
    }
}
