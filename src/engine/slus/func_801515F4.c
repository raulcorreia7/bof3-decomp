#include "engine/slus/slus.h"

/* increments g_UiMessageStep[0] when D_80148357 is 2.
 */
MATCH void func_801515F4(void) {
    if (g_UiPanelTasks[1].state == 2) {
        /* FAKE: retail addresses g_UiMessageStep as an array element; the scalar spelling folds the address. */
        MEM(u8, (u32)&g_UiMessageStep) += 1;
    }
}
