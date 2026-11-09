#include "engine/slus/slus.h"

/* dispatches through the two-entry callback table on g_UiWindowStep. */
MATCH void func_80150F3C(void) {
    void (*table[2])(void) = {func_80150F8C, func_8015102C};

    table[g_UiWindowStep]();
}
