#include "area117_13.h"

MATCH void func_801F34C8(void) {
    u8* flags;

    flags = D_80144ED0;
    if (!SYS_TestFlag(flags, D_801F463C[g_Task->param.unk_0B])) {
        g_Task->timer = 9;
        g_Task->header.step++;
    }
    func_801F3884(g_Task->param.unk_0B + SYS_TestFlag(flags, D_801F4640[g_Task->param.unk_0B]) * 4 + 1, 0x40);
    func_801F3AF8();
}
