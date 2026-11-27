#include "area135_14.h"

MATCH void func_801F61A8(s32 message) {
    UI_MessageStartArea(message & BYTE_MASK);
    g_UIPanelCurrent = g_UIPanelTasks;
    UI_PanelClear();
    g_UIPanelTasks[0].pos.vx = 0x3C0;
    g_UIPanelTasks[0].pos.vy = 0xAA0;
}
