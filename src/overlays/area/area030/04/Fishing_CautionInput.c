#include "area030_04.h"

/* Scans the table range, bumps the work phase when either mask is
 * set, then calls the shared tail with the second mask. */
/* func_801DA498 */
MATCH void Fishing_CautionInput(void) {
    Fishing_DrawCautionBox(68, 78);
    if (g_PadStates[0].pressed & (g_InputMasks[FISHING_INPUT_CAST] | g_InputMasks[FISHING_INPUT_CANCEL])) {
        SELF(FishingState)->sub_index += 1;
    }
    Fishing_DrawDimScreen();
}
