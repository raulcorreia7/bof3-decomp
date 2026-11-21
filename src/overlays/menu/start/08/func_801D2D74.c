#include "start_08.h"

/* gcc 2.7.2 needs the declaration form to emit the direct symbol store this function matched with. */
extern volatile u8 D_80148594; /* local: volatile access; the shared copy is plain */

MATCH void func_801D2D74(void) {
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].active = 0;
    D_80148504.active                                = 0;
    g_UiPanelTasks[14].active                        = 0;
    D_8014854C                                       = 0;
    g_UiPanelTasks[16].active                        = 0;
    g_UiPanelTasks[17].active                        = 0;
}
