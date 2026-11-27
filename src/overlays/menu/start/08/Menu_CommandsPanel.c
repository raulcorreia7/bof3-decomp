#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

/* func_801EA0B0 */
MATCH void Menu_CommandsPanel(void) {
    g_MenuStartCommandsSteps[g_UiPanelCurrent->state]();
    /* clang-format off */
    Menu_DrawCommandRow(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy,
                        g_UiPanelCurrent->unk_0A, g_UiPanelCurrent->unk_0B, 0);
    /* clang-format on */
}
