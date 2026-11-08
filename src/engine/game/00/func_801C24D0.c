#include "game_00.h"

/* The retail code never reads $a0-$a2; the slus caller's arguments are leftover register values kept in its prototype.
*/
MATCH void func_801C24D0(void) {
    func_801C2538();
    if ((SCRATCH_WORK->unk_05 == 0) &&
        !((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        func_801C2710();
    }
}
