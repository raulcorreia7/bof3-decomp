#include "battle_15.h"

MATCH void func_800A8BD0(void) {
    u8* work;
    u8* saved;

    BATTLE_ACTIVE_PARTY.header.flags &= ~ACTOR_FLAG_HIDDEN;
    work  = (u8*)D_801EB4E0;
    saved = TASK_BYTES;
    TASK_SET(work);
    Actor_SelectScript((work[8] + 4) & 0xFF);
    TASK_SET(saved);
    func_801E5988();
}
