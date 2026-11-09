#include "engine/slus/slus.h"

/* decrements g_MessageChoiceStep when the D_801490BA countdown is 2, and steps the
 * countdown up by two otherwise.
 */
/* func_80151A48 */
MATCH void UI_PrevChoice(void) {
    s8 value;

    value = D_801490BA[0];
    if (value == 2) {
        g_MessageChoiceStep = g_MessageChoiceStep - 1;
    } else {
        D_801490BA[0] = value + 2;
    }
}
