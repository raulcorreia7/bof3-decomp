#include "engine/slus/slus.h"

/* advances g_UIMessageChoiceStep when the D_801490BA countdown is -2, and steps the
 * countdown down by two otherwise.
 */
/* func_801519F8 */
MATCH void UI_MessageNextChoice(void) {
    s8 value;

    value = D_801490BA[0];
    if (value == -2) {
        g_UIMessageChoiceStep = g_UIMessageChoiceStep + 1;
    } else {
        D_801490BA[0] = value - 2;
    }
}
