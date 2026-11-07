#include "start_08.h"

MATCH void func_801D28C8(void) {
    u8* counter;
    u8  count;
    s32 i;

    Menu_DrawClutStrip(D_80144953);
    counter = &D_80148654;
    count   = *counter;
    count--;
    *counter = count;
    if (count == 0) {
        func_801D2D74();
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            g_MenuPanelTasks[i + 4].state = 4;
            i++;
        }
        g_MenuPanelTasks[7].state  = 2;
        g_MenuPanelTasks[8].state  = 2;
        g_MenuPanelTasks[9].state  = 2;
        g_MenuPanelTasks[10].state = 2;
        D_80148654                 = 0;
        D_80148650                 = 1;
        D_80148651                 = 0;
    }
}
