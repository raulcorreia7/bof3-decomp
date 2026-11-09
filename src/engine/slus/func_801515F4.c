#include "engine/slus/slus.h"

/* increments g_UiWindowStep[0] when D_80148357 is 2. */
MATCH void func_801515F4(void) {
    if (D_80148357 == 2) {
        /* FAKE: retail addresses g_UiWindowStep as an array element; the scalar spelling folds the address. */
        MEM(u8, (u32)&g_UiWindowStep) += 1;
    }
}
