#include "start_08.h"

MATCH void func_801D3768(void) {
    u8* counter;
    u8  count;
    u8  value;
    u8  i;

    Menu_DrawClutStrip(D_80144953);
    counter  = &D_80148654;
    count    = *counter - 1;
    *counter = count;
    if (count == 0) {
        func_801D528C();
        i     = 0;
        value = 3;
        for (; i < Party_CountOrder(0); i++) {
            D_80148333[((i + 4) * 9) << 2] = value;
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
