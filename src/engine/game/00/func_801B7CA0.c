#include "game_00.h"

MATCH void func_801B7CA0(void) {
    if ((Area_ClimbDismountExit() & BYTE_MASK) && (TASK(Actor)->unk_05 == 0)) {
        g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
    }
}
