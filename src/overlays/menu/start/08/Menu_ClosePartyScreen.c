#include "start_08.h"

/* func_801DA984 */
MATCH void Menu_ClosePartyScreen(void) {
    u8* counter;
    u8  count;
    u8  value;
    u8  i;

    Menu_DrawClutStrip(g_WindowClut);
    counter  = &D_80148654;
    count    = *counter - 1;
    *counter = count;
    if (count == 0) {
        func_801DB510();
        i     = 0;
        value = 4;
        for (; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
            g_UIPanelTasks[i + 4].state = value;
        }
        g_UIPanelTasks[7].state  = 2;
        g_UIPanelTasks[8].state  = 2;
        g_UIPanelTasks[9].state  = 2;
        g_UIPanelTasks[10].state = 2;
        D_80148654               = 5;
        g_MenuStep.step          = 1;
        g_MenuStep.sub_step      = 0;
    }
}
