#include "area196_13.h"

MATCH void func_801F2CF0(void) {
    u8 temp_v1;

    if (g_AreaSceneMode == 2) {
        g_Task->step += 1;
    }
    temp_v1 = g_Task->unk_09;
    if (temp_v1 < 0x20U) {
        g_Task->unk_09 = temp_v1 + 1;
    }
    func_801F3030(0x20 - g_Task->unk_09);
    g_Task->unk_0A += 1;
    g_Task->unk_0A &= 0x3F;
    func_801F3850();
}
