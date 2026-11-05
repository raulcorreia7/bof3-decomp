#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 temp_v0;

    if (!(g_Task->unk_09 & 3)) {
        func_801F48B0();
    }
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->mode += 1;
    }
    func_801F49A0();
}
