#include "engine/slus/slus.h"

/* clears g_UiMessageState when the message panel state is 2.
 */
MATCH void func_80151820(void) {
    if (g_UiPanelTasks[0].state == 2) {
        g_UiMessageState.state = 0;
    }
}
