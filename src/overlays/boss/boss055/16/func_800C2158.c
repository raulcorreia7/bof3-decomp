#include "boss055_16.h"

MATCH void func_800C2158(void) {
    u16* state;

    func_801E3160();
    if (g_BattleCurrentEnemy->unk_F5 == 4) {
        g_BattleCurrentEnemy->ap -= D_801463C8;
    }
    state = &g_BattleState;
    *state |= 0x800;
    g_BattleCurrentEnemy->unk_F5 = 0;
    ((PartyBattler*)g_SpadWork)->unk_02 += 1;
}
