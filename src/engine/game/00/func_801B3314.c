#include "game_00.h"

MATCH void func_801B3314(void) {
    func_801C4D58();
    if ((g_Task->unk_05 == 0) &&
        ((g_GameFlags | g_AreaWalkFlags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0) {
        func_801C2710();
    }
    g_Task->unk_03 = 1;
}
