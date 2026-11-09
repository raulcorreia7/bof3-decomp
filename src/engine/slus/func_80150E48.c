#include "engine/slus/slus.h"

/* dispatches through the two-entry callback table on g_UiWindowStep.
 */
MATCH void func_80150E48(void) {
    void (*table[2])(void) = {func_80150E98, func_80150F08};

    table[g_UiWindowStep]();
}
