#include "game_00.h"

MATCH void func_801A3A08(void) {
    Actor* work;
    u16    mode;

    work = g_Task;
    if (!(work->header.flags & ACTOR_FLAG_HIDDEN)) {
        mode = work->unk_06;
        /* Retail shares one dispatch tail for both mode tests. */
        if ((u8)mode == 1 || (u32)(mode - 3) < 2)
            goto dispatch; /* the mode selects the shared dispatch tail */
    } else if (work->unk_06 == 4) {
        goto dispatch; /* Retail shares one dispatch tail for both mode tests. */
    }
    if ((((Actor*)g_CurrentActor)->unk_94 & 0x7F) != 0x7F) {
    dispatch:
        func_801ACE10(g_BattlePartyBattlers[0].chr.character_id);
    } else {
        GAME_WORK_AREA_PTR->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    }
}
