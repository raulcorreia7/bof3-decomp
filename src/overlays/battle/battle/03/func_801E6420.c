#include "battle_03.h"

MATCH void func_801E6420(void) {
    BattleEffect* slot;

    func_801DE560(1, 0, 0, 30, BATTLER_IS_PLAYER(g_Battle.active_battler) ? D_801EB05B : D_801EB068);
    slot                 = D_801EC2E0;
    g_BattleMessageState = 1;
    slot->arg.unk_09     = 2;
    slot->unk_0C         = 0x100;
    slot->unk_10         = 0;
    D_801EC2E0->header.mode++;
}
