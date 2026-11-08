#include "area135_14.h"

MATCH void func_801F44E0(void) {
    u8 slot = g_GameState - g_Game.members;

    if (slot != 0) {
        g_Task->direction_08 = g_Game.members[0].facing;
        Actor_SelectScript(g_Task->direction_08);
    }
}
