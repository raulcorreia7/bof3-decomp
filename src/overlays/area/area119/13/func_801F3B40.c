#include "area119_13.h"

MATCH void func_801F3B40(void) {
    if (g_AreaSceneMode != 0) {
        SELF(Actor)->timer        = 1;
        SELF(Actor)->param.unk_0B = 0;
        SELF(Actor)->header.step++;
    }
}
