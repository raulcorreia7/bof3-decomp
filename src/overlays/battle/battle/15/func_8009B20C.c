#include "battle_15.h"

MATCH void func_8009B20C(void) {
    u8  i;
    u8* base;
    u8* ptr;

    i    = 0x10;
    base = (u8*)g_MenuPanelTasks;
    do {
        ptr                = (u8*)(i * 0x24u + (u32)base);
        g_MenuCurrentPanel = (MenuPanelTask*)ptr;
        i += 1;
        Menu_ClearPanel();
    } while (i < 20);
}
