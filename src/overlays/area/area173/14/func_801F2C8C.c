#include "area173_14.h"

MATCH void func_801F2C8C(void) {
    g_SpadWork->unk_09 = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0x80)) {
        g_SpadWork->state_02 = 5;
    } else {
        g_SpadWork->state_02++;
    }
}
