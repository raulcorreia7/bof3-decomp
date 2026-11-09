#include "engine/slus/slus.h"

/* dispatches through the two-entry callback table on g_UiWindowStep.
 */
MATCH void func_80151844(void) {
    void (*table[2])(void) = {func_80151894, func_80150F08};

    table[g_UiWindowStep]();
}
