#include "area196_13.h"

MATCH void func_801F2DB0(void) {
    if (g_AreaSceneMode == 3) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
    func_801F3030(0);
    g_Task->unk_0A = g_Task->unk_0A + 2;
    g_Task->unk_0A = g_Task->unk_0A & 0x3F;
    func_801F3850();
}
