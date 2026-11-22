#include "area135_14.h"

MATCH void func_801F44E0(void) {
    u8 slot = g_GameState - g_Game.members;

    if (slot != 0) {
        TASK(Actor)->direction = g_Game.members[0].facing;
        Script_Select(TASK(Actor)->direction);
    }
}
