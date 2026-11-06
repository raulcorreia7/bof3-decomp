#include "start_08.h"

extern u8 D_80148656; /* local: u8 read; a sibling copy is s8 */

MATCH void func_801D8BA0(void) {
    s32 i;
    s32 off;
    s32 temp;
    u8* cell;

    Menu_DrawClutStrip(D_80144953);
    cell  = &D_80148654;
    temp  = *cell - 1;
    *cell = temp;
    if (!(temp & BYTE_MASK)) {
        func_801D96D4();
        i   = 0;
        off = 0x90;
        while (i < (Party_CountOrder(0) & BYTE_MASK)) {
            i++;
            temp             = off;
            D_80148333[temp] = 4;
            off += 0x24;
        }
        g_MenuPanelTasks[7].state  = 2;
        g_MenuPanelTasks[8].state  = 2;
        g_MenuPanelTasks[9].state  = 2;
        g_MenuPanelTasks[10].state = 2;
        D_80148654                 = 0;
        D_80148650                 = 1;
        D_80148651                 = 0;
        D_80148665                 = D_80148656;
    }
}
