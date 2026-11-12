#include "area148_13.h"

MATCH void func_801F361C(void) {
    s32 arg0;
    s32 arg1;

    if (SYS_TestFlag(g_SceneEventFlags, 90) != 0) {
        arg0                  = 0;
        arg1                  = -2;
        (g_Task)->screen_y    = 128;
        (g_Task)->header.step = 3;
    } else {
        (g_Task)->screen_y = 0;
        (g_Task)->header.step += 1;
        func_801F37B8(0, 1);
        arg0 = 1;
        arg1 = 1;
    }
    func_801F37B8(arg0, arg1);
}
