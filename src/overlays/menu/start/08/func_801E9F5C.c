#include "start_08.h"

MATCH void func_801E9F5C(void) {
    g_MenuStartPanel12StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawInventoryWindow(g_MenuCurrentPanel);
}
