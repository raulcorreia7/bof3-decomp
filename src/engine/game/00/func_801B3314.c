#include "game_00.h"

MATCH void func_801B3314(void) {
    func_801C4D58();
    if ((TASK(Actor)->unk_05 == 0) && ((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0) {
        Area_ScrollUpdateWalk();
    }
    TASK(Actor)->unk_03 = 1;
}
