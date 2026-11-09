#include "area104_14.h"

MATCH void func_801F5738(void) {
    FIELD(s32, g_Task, 0x34) = g_Game.members[0].pos.x.fixed;
    FIELD(s32, g_Task, 0x38) = g_Game.members[0].pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Game.members[0].pos.z);
    func_8015A944();
    func_801F564C();
}
