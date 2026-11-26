#include "area103_13.h"

MATCH void func_801F4030(void) {
    if (SELF(Actor)->timer % 5 == 0) {
        func_801F4E70(SELF(Actor)->timer / 5 + 4);
    }
    SELF(Actor)->timer++;
    func_801F49A0(1);
    if (SELF(Actor)->timer / 5 == 3) {
        g_AreaSceneMode    = 0;
        SELF(Actor)->timer = 1;
        SELF(Actor)->header.step++;
    }
}
