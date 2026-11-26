#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

/* func_801E98F8 */
MATCH void Menu_EquipmentPanel(void) {
    g_MenuStartEquipmentSteps[g_UiPanelCurrent->state]();
    Menu_DrawEquipmentPanel(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, g_CharSlot[g_PartyFieldOrder[g_UiPanelCurrent->unk_0A]]);
}
