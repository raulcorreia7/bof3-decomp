#include "area121_14.h"

MATCH void func_801F5C7C(void) {
    SELF(Actor)->pos.x.fixed      = g_Game.members[0].pos.x.fixed;
    SELF(Actor)->pos.y.fixed      = g_Game.members[0].pos.y.fixed;
    COORD_INT(SELF(Actor)->pos.z) = COORD_INT(g_Game.members[0].pos.z);
    Actor_ProjectForDraw();
    func_801F5B90();
}
