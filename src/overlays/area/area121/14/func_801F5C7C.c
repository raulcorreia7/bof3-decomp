#include "area121_14.h"

MATCH void func_801F5C7C(void) {
    FIELD(s32, g_Task, 0x34u) = D_80145EC4[0];
    FIELD(s32, g_Task, 0x38u) = D_80145EC8;
    g_Task->z.part.integer    = D_80145ECE;
    func_8015A944();
    func_801F5B90();
}
