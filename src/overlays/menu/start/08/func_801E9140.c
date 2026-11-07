#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

MATCH void func_801E9140(void) {
    g_MenuStartPanel1StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawZennyWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0, g_Zenny);
}
