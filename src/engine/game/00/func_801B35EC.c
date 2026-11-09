#include "game_00.h"

MATCH void func_801B35EC(void) {
    if (func_801C539C() & BYTE_MASK) {
        if ((g_Task->unk_05 == 0) && ((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0) {
            func_801C2710();
        }
        g_Task->unk_03 = 3;
    }
}
