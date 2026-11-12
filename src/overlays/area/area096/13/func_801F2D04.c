#include "area096_13.h"
#include "area/spad.h"

MATCH void func_801F2D04(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 32) != 0) {
        g_AreaSceneMode      = 1;
        g_Task->pos.z.fixed  = -0x100;
        g_Task->param.unk_0B = 0x80;
        g_Task->timer        = 10;
        g_Task->header.step++;
        func_801F2ECC(-0x100, 0x80);
    }
}
