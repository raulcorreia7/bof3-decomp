#include "start_08.h"

MATCH void func_801E9224(void) {
    D_801ED3BC[g_MenuCurrentPanel->state]();
    Menu_DrawPlayTimeWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y);
}
