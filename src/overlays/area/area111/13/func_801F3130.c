#include "area111_13.h"

MATCH void func_801F3130(void) {
    SELF(Actor)->screen_y = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 40) != 0) {
        Actor_Clear();
        return;
    }
    SELF(Actor)->header.step++;
    func_801F3244();
}
