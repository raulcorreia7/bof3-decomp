#include "area135_14.h"

MATCH void func_801F61A8(s32 message) {
    UI_MessageStartArea(message & BYTE_MASK);
    g_UiPanelCurrent = g_UiPanelTasks;
    UI_PanelClear();
    g_UiPanelTasks[0].pos.vx = 0x3C0;
    g_UiPanelTasks[0].pos.vy = 0xAA0;
}
