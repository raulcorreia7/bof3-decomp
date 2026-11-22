#include "game_00.h"

MATCH void func_801B7D44(void) {
    func_801C4D58();
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    TASK(Actor)->unk_04 = 1;
}
