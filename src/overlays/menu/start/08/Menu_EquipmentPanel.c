#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

/* func_801E98F8 */
MATCH void Menu_EquipmentPanel(void) {
    g_MenuStartEquipmentStates[g_MenuCurrentPanel->state]();
    Shop_DrawEquipment(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                       g_CharSlot[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0A]]);
}
