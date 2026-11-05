#include "battle_03.h"

/* clears one local work flag bit, then either integrates the local
 * velocity or resets the step and clears the selected record's pending flag.
 */
MATCH void func_801E7778(void) {
    PartyBattler* work;
    u8            flag;
    u32           index;
    u32           step;
    u32           value;

    D_801EB4E0->flags &= ~ACTOR_FLAG_HIDDEN;
    work = D_801EB4E0;
    step = work->unk_40;
    if (step != 0x10000) {
        work->unk_40 = step + 0x2000;
    } else {
        work->unk_48                                 = 0;
        index                                        = D_801EB4E0->slot;
        value                                        = g_BattlePartyBattlers[index].flags_124.value & 0xFFFFDFFFu;
        g_BattlePartyBattlers[index].flags_124.value = value;
        func_801E5988();
    }
}
