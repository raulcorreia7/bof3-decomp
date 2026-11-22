#include "area103_13.h"

MATCH void func_801F4030(void) {
    if (TASK(Actor)->timer % 5 == 0) {
        func_801F4E70(TASK(Actor)->timer / 5 + 4);
    }
    TASK(Actor)->timer++;
    func_801F49A0(1);
    if (TASK(Actor)->timer / 5 == 3) {
        g_AreaSceneMode    = 0;
        TASK(Actor)->timer = 1;
        TASK(Actor)->header.step++;
    }
}
