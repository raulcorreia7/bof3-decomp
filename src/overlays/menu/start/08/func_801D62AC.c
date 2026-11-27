#include "start_08.h"

extern u8 D_80148656; /* local: u8 read; a sibling copy is s8 */

MATCH void func_801D62AC(void) {
    s32 i;
    s32 off;
    s32 temp;
    u8* cell;

    Menu_DrawClutStrip(g_WindowClut);
    cell  = &D_80148654;
    temp  = *cell + 1;
    *cell = temp;
    if ((temp & BYTE_MASK) == 4) {
        func_801D71EC();
        i   = 0;
        off = 0x90;
        while (i < (Party_CountOrder(PARTY_ORDER_FIELD) & BYTE_MASK)) {
            i++;
            temp                             = off;
            (&g_UIPanelTasks[0].state)[temp] = 4;
            off += 0x24;
        }
        g_UIPanelTasks[7].state  = 2;
        g_UIPanelTasks[8].state  = 2;
        g_UIPanelTasks[9].state  = 2;
        g_UIPanelTasks[10].state = 2;
        D_80148654               = 0;
        g_MenuStep.step          = 1;
        g_MenuStep.sub_step      = 0;
        D_80148663               = D_80148656;
    }
}
