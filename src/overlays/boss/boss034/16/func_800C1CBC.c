#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    func_8014D978();
    if (EMI_LoaderIsReady() != 0) {
        func_801E54EC();
        ((PartyBattler*)g_Task)->flags &= 0xBF;
        ((PartyBattler*)g_Task)->mode   = 6;
        ((PartyBattler*)g_Task)->step   = 4;
        ((PartyBattler*)g_Task)->unk_03 = 6;
    }
}
