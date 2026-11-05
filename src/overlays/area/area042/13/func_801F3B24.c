#include "area042_13.h"

MATCH void func_801F3B24(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(g_Task->x)]) == 0) {
        g_Task->unk_09 = 0;
        g_Task->step += 1;
    }
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 0x41U) {
        g_Task->unk_09 = 0;
        if ((rand() & 1) != 0) {
            g_Task->step = 5;
        }
    }
}
