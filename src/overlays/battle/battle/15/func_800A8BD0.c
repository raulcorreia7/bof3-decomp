#include "battle_15.h"

MATCH void func_800A8BD0(void) {
    u8* work;
    u8* saved;

    BATTLE_ACTING_PARTY.flags_00 &= ~ACTOR_FLAG_HIDDEN;
    work       = (u8*)D_801EB4E0;
    saved      = SPAD_WORK_BYTES;
    g_SpadWork = (struct Task*)work;
    Actor_SelectScript((work[8] + 4) & BYTE_MASK);
    g_SpadWork = (struct Task*)saved;
    func_801E5988();
}
