#include "start_08.h"

MATCH void func_801DA984(void) {
    u8* counter;
    u8  count;
    u8  value;
    u8  i;

    Menu_DrawClutStrip(D_80144953);
    counter  = &D_80148654;
    count    = *counter - 1;
    *counter = count;
    if (count == 0) {
        func_801DB510();
        i     = 0;
        value = 4;
        for (; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
            g_MenuPanelTasks[i + 4].state = value;
        }
        g_MenuPanelTasks[7].state  = 2;
        g_MenuPanelTasks[8].state  = 2;
        g_MenuPanelTasks[9].state  = 2;
        g_MenuPanelTasks[10].state = 2;
        D_80148654                 = 5;
        g_MenuStep.step            = 1;
        g_MenuStep.sub_step        = 0;
    }
}
