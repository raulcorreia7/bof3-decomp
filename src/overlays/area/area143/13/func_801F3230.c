#include "area143_13.h"

MATCH void func_801F3230(void) {
    if (g_AreaSceneMode != 1) {
        return;
    }
    g_Task->param.unk_0B = 0;
    g_Task->pos.z.fixed  = 0;
    g_Task->header.step += 1;
}
