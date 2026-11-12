#include "area174_13.h"

MATCH void func_801F2D68(void) {
    s32 result;

    if (!(g_Task->timer & 0x7)) {
        result = func_801F2E88();
        if (result != 0) {
            func_801F3378(result);
        }
    }
    g_Task->timer += 1;
    if (g_Task->unk_06 != 0) {
        Area_UpdateShots();
    }
    if (D_80147A8C == TO_COORD(64) + COORD_HALF) {
        g_Task->header.mode += 1;
    }
}
