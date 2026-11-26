#include "area135_14.h"

MATCH void func_801F3B88(void) {
    Actor* work;
    s32    value;

    work              = SELF(Actor);
    value             = work->pos.z.fixed - 8;
    g_AreaSceneMode   = 0;
    work->pos.z.fixed = value;
    if (value < -0x17F) {
        Area_CellSetPalette(39, 47);
        SELF(Actor)->header.step++;
    }
    func_801F3CA8();
}
