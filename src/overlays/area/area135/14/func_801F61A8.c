#include "area135_14.h"

MATCH void func_801F61A8(s32 message) {
    Message_StartAreaMessage(message & BYTE_MASK);
    g_MenuCurrentPanel = g_MenuPanelTasks;
    Menu_ClearPanel();
    D_80148334 = 0x3C0;
    D_80148336 = 0xAA0;
}
