#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    func_8014D978();
    if (EMI_LoaderIsReady() != 0) {
        func_801E54EC();
        ((PartyBattler*)g_SpadWork)->flags_00 &= 0xBF;
        ((PartyBattler*)g_SpadWork)->step_01 = 6;
        ((PartyBattler*)g_SpadWork)->unk_02  = 4;
        ((PartyBattler*)g_SpadWork)->unk_03  = 6;
    }
}
