#include "battle_03.h"

MATCH void func_801D93E4(u8 mode) {
    UI_PanelOpenTask(3u, 3u);
    g_UiPanelTasks[3].mode  = 2u;
    g_UiPanelTasks[3].state = mode;
}
