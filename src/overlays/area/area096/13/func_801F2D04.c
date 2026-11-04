#include "area096_13.h"
#include "work/area_spad.h"

MATCH void func_801F2D04(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x20) != 0) {
        g_AreaSceneMode = 1;
        g_SpadWork->z.fixed = -0x100;
        g_SpadWork->unk_0B = 0x80;
        g_SpadWork->unk_09 = 0xA;
        g_SpadWork->state_02++;
        func_801F2ECC(-0x100, 0x80);
    }
}
