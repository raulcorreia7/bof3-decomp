#include "engine/slus/slus.h"

/* advances g_MessageChoiceStep when the D_801490BA countdown is -2, and steps the
 * countdown down by two otherwise.
 */
MATCH void func_801519F8(void) {
    s8 value;

    value = D_801490BA[0];
    if (value == -2) {
        g_MessageChoiceStep = g_MessageChoiceStep + 1;
    } else {
        D_801490BA[0] = value - 2;
    }
}
