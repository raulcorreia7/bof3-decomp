#include "battle_03.h"

MATCH void func_801D9388(u8 index) {
    UI_PanelOpenTask(2u, 3u);
    g_UIPanelTasks[2].mode  = 1u;
    D_8014837C              = 0x0088u;
    g_UIPanelTasks[2].state = index;
    D_8014837E              = 0x0058u;
}
