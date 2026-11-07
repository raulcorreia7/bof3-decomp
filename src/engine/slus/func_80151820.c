#include "engine/slus/slus.h"

/* clears g_MessageState when the message panel state is 2.
 */
MATCH void func_80151820(void) {
    if (g_MenuPanelTasks[0].state == 2) {
        g_MessageState.state_00 = 0;
    }
}
