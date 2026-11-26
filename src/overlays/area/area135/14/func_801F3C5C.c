#include "area135_14.h"

MATCH void func_801F3C5C(void) {
    Actor* work;
    s32    value;

    work            = SELF(Actor);
    value           = work->pos.z.fixed;
    g_AreaSceneMode = 0;
    value += 8;
    work->pos.z.fixed = value;
    if (value >= -0x90) {
        SELF(Actor)->header.step = 1;
    }
    func_801F3CA8();
}
