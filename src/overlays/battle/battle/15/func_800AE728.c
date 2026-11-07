#include "battle_15.h"

/* EXE-side pointer to the shared battle state record. */

MATCH void func_800AE728(void) {
    PartyBattler* work;
    u8            next;

    work         = (PartyBattler*)g_Task;
    next         = work->unk_09 + 1;
    work->unk_09 = next;
    if (next == 0x1C) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801E5988();
    }
}
