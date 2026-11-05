#include "area042_13.h"

MATCH void func_801F3B24(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[g_SpadWork->x.part.integer]) == 0) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
    g_SpadWork->unk_09 += 1;
    if (g_SpadWork->unk_09 >= 0x41U) {
        g_SpadWork->unk_09 = 0;
        if ((rand() & 1) != 0) {
            g_SpadWork->state_02 = 5;
        }
    }
}
