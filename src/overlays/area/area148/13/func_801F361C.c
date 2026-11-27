#include "area148_13.h"

MATCH void func_801F361C(void) {
    s32 mode;
    s32 value;

    if (SYS_TestFlag(g_SceneEventFlags, 90) != 0) {
        mode                     = 0;
        value                    = -2;
        SELF(Actor)->screen_y    = 128;
        SELF(Actor)->header.step = 3;
    } else {
        SELF(Actor)->screen_y = 0;
        SELF(Actor)->header.step += 1;
        func_801F37B8(0, 1);
        mode  = 1;
        value = 1;
    }
    func_801F37B8(mode, value);
}
