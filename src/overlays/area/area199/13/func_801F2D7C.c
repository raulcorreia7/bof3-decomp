#include "area199_13.h"

MATCH void func_801F2D7C(void) {
    Actor* scratch;

    ORDER_LOCK_BEGIN
        scratch              = g_Task;
        g_AreaSceneMode      = 0;
        scratch->pos.x.fixed = 0x54;
        scratch->pos.y.fixed = 0;
        scratch->pos.z.fixed = 0;
        D_801F54D0[0]        = 0x7E;
        D_801F54D0[1]        = 0x14;
        D_801F54D0[2]        = 1;
        D_801F54D0[3]        = 0x54;
        D_801F54D0[4]        = 0x13;
        D_801F54D0[5]        = 0;
    ORDER_LOCK_END;
}
