#include "engine/slus/slus.h"

/* sets bit 1 of g_UiWindowChannel when the message panel state is 4.
 */
MATCH void func_80150F08(void) {
    if (g_MenuPanelTasks[0].state == 4) {
        volatile u16* h = &g_UiWindowChannel;
        *h |= FRONTEND_FLAG_CONFIRM;
    }
}
