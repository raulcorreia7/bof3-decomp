#include "area119_13.h"

MATCH void func_801F3170(void) {
    if (g_AreaSceneMode != 0) {
        return;
    }
    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(66) + COORD_HALF)) > (TO_COORD(1) + COORD_HALF)) {
        SELF(Actor)->header.step = 4;
        return;
    }
    if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(62)) <= (TO_COORD(1) + COORD_HALF)) {
        return;
    }
    if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(63)) <= (TO_COORD(1) + COORD_HALF)) {
        return;
    }
    SELF(Actor)->header.step = 4;
}
