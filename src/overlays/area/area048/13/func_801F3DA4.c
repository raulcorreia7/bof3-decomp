#include "area048_13.h"

MATCH void func_801F3DA4(void) {
    g_SpadWork->unk_09 = 0;
    if (g_SpadWork->x.part.integer == 0 && SYS_TestFlag(g_SceneEventFlags, 0xD) != 0) {
        func_801F41F0(0, 3);
        g_SpadWork->state_02 = 3;
    } else {
        func_801F41F0(g_SpadWork->x.part.integer, 0);
        g_SpadWork->state_02 = 1;
    }
}
