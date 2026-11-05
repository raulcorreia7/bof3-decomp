#include "area104_14.h"

MATCH void func_801F5738(void) {
    FIELD(s32, g_Task, 0x34) = D_80145EC4;
    FIELD(s32, g_Task, 0x38) = D_80145EC8;
    g_Task->z.part.integer   = D_80145ECE;
    func_8015A944();
    func_801F564C();
}
