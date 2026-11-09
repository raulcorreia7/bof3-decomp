#include "area041_13.h"

MATCH void func_801F2DA8(void) {
    if (SYS_TestFlag(&g_SceneFlagWords[D_801F42CC[g_Task->param.unk_0B] * 8], D_801F42D0[g_Task->param.unk_0B])) {
        g_Task->timer = 0;
        g_Task->header.step++;
    }
    func_801F2EFC();
    func_801F3064();
}
