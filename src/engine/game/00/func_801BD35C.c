#include "game_00.h"

MATCH void func_801BD35C(void) {
    if (!(g_Game.walk_flags & AREA_WALK_MENU_ACTIVE)) {
        g_Task->header.mode = 1;
    }
}
