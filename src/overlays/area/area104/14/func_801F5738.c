#include "area104_14.h"

MATCH void func_801F5738(void) {
    g_Task->pos.x.fixed      = g_Game.members[0].pos.x.fixed;
    g_Task->pos.y.fixed      = g_Game.members[0].pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Game.members[0].pos.z);
    Actor_ProjectForDraw();
    func_801F564C();
}
