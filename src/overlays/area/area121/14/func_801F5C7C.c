#include "area121_14.h"

MATCH void func_801F5C7C(void) {
    FIELD(s32, g_Task, 0x34u) = g_Game.members[0].pos.x.fixed;
    FIELD(s32, g_Task, 0x38u) = g_Game.members[0].pos.y.fixed;
    COORD_INT(g_Task->pos.z)  = D_80145ECE;
    func_8015A944();
    func_801F5B90();
}
