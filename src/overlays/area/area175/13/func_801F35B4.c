#include "area175_13.h"

MATCH void func_801F35B4(void) {
    func_801F36DC((s16)g_Task->unk_2E, (s16)g_Task->unk_30, g_Task->unk_09);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 0x1FU) {
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}
