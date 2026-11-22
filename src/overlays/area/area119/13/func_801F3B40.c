#include "area119_13.h"

MATCH void func_801F3B40(void) {
    if (g_AreaSceneMode != 0) {
        TASK(Actor)->timer        = 1;
        TASK(Actor)->param.unk_0B = 0;
        TASK(Actor)->header.step++;
    }
}
