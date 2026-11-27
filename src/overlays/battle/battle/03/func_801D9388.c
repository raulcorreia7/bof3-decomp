#include "battle_03.h"

MATCH void func_801D9388(u8 index) {
    UI_PanelOpenTask(2u, 3u);
    g_UiPanelTasks[2].mode   = 1u;
    g_UiPanelTasks[2].pos.vx = 0x0088u;
    g_UiPanelTasks[2].state  = index;
    g_UiPanelTasks[2].pos.vy = 0x0058u;
}
