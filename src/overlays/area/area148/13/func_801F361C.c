#include "area148_13.h"

MATCH void func_801F361C(void) {
    s32 arg0;
    s32 arg1;

    if (SYS_TestFlag(g_SceneEventFlags, 0x5A) != 0) {
        arg0                           = 0;
        arg1                           = -2;
        ((Actor*)g_SpadWork)->unk_30   = 0x80;
        ((Actor*)g_SpadWork)->state_02 = 3;
    } else {
        ((Actor*)g_SpadWork)->unk_30 = 0;
        ((Actor*)g_SpadWork)->state_02 += 1;
        func_801F37B8(0, 1);
        arg0 = 1;
        arg1 = 1;
    }
    func_801F37B8(arg0, arg1);
}
