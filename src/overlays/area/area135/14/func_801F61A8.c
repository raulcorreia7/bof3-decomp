#include "area135_14.h"

MATCH void func_801F61A8(s32 message) {
    UI_MessageStartArea(message & BYTE_MASK);
    g_UiPanelCurrent = g_UiPanelTasks;
    UI_PanelClear();
    D_80148334 = 0x3C0;
    D_80148336 = 0xAA0;
}
