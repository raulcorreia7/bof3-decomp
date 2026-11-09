#include "engine/slus/slus.h"

/* counts g_MessageStateTimer down and. */
MATCH void func_80151894(void) {
    u8  value;
    u8  mode;
    u8  index;
    int flags;
    u8  advance;

    value                  = g_MessageStateTimer[0];
    g_MessageStateTimer[0] = value + 0xFF;
    if (value == 0) {
        advance = g_MenuPanelTasks[0].state + 1;
        index   = g_UiWindowStep + 1;
        mode    = advance;
        flags   = g_UiWindowChannel;
        flags |= FRONTEND_FLAG_SELECTION;
        g_MenuPanelTasks[0].state = mode;
        g_UiWindowStep            = index;
        g_UiWindowChannel         = flags;
    }
}
