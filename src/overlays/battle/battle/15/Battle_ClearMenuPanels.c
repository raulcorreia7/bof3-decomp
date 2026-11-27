#include "battle_15.h"

/* func_8009B20C */
MATCH void Battle_ClearMenuPanels(void) {
    u8  i;
    u8* base;
    u8* ptr;

    i    = 0x10;
    base = (u8*)g_UIPanelTasks;
    do {
        ptr              = (u8*)(i * 0x24u + (u32)base);
        g_UIPanelCurrent = (MenuPanelTask*)ptr;
        i += 1;
        UI_PanelClear();
    } while (i < 20);
}
