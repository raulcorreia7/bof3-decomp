#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

/* func_801EA0B0 */
MATCH void Menu_CommandsPanel(void) {
    g_MenuStartCommandsSteps[g_UIPanelCurrent->state]();
    /* clang-format off */
    Menu_DrawCommandRow(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy,
                        g_UIPanelCurrent->unk_0A, g_UIPanelCurrent->unk_0B, 0);
    /* clang-format on */
}
