#include "game_00.h"

MATCH void func_801B7CA0(void) {
    if ((func_801C5474() & BYTE_MASK) && (SCRATCH_WORK->unk_05 == 0)) {
        g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
    }
}
