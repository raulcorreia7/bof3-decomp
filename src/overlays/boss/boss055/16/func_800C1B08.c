#include "boss055_16.h"

MATCH void func_800C1B08(void) {
    u8 timer;

    timer                           = ((PartyBattler*)g_Task)->unk_09 - 1;
    ((PartyBattler*)g_Task)->unk_09 = timer;
    if (timer == 0) {
        func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
    }
    ((PartyBattler*)g_Task)->unk_0B = 0;
}
