#include "area199_13.h"

MATCH void func_801F2D7C(void) {
    Actor* scratch;

    do {
        scratch = g_SpadWork;
        g_AreaSceneMode = 0;
        scratch->x.fixed = 0x54;
        scratch->y.fixed = 0;
        scratch->z.fixed = 0;
        D_801F54D0[0] = 0x7E;
        D_801F54D0[1] = 0x14;
        D_801F54D0[2] = 1;
        D_801F54D0[3] = 0x54;
        D_801F54D0[4] = 0x13;
        D_801F54D0[5] = 0;
    } while (0);
}
