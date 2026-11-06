#include "area135_14.h"

MATCH void func_801F61A8(s32 message) {
    Message_StartAreaMessage(message & 0xFF);
    g_MenuCurrentPanel = g_MenuPanelTasks;
    func_80158E20();
    D_80148334 = 0x3C0;
    D_80148336 = 0xAA0;
}
