#include "start_08.h"

MATCH void func_801DB67C(void) {
    u8  i;
    u8  value;
    s16 offset;

    Menu_DrawClutStrip(g_WindowClut);
    i      = 0;
    value  = 4;
    offset = -0x96;
    for (; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
        g_UiPanelTasks[i + 4].state  = value;
        g_UiPanelTasks[i + 4].pos.vx = offset;
    }
    g_UiPanelTasks[7].state  = 2;
    g_UiPanelTasks[8].state  = 2;
    g_UiPanelTasks[9].state  = 2;
    g_UiPanelTasks[10].state = 2;
    D_80148654               = 0;
    g_MenuStep.step          = 1;
    g_MenuStep.sub_step      = 0;
    g_MenuStep.state         = 0;
    D_80148655               = D_801ED6A0;
}
