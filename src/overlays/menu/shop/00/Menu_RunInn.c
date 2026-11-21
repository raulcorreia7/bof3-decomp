#include "shop_00.h"

/* Mode table for the shop's current menu state, indexed by the shared
 * shop-state byte g_MenuStep.sub_step. */

/* func_801D39BC */
MATCH void Menu_RunInn(void) {
    SYS_DISPATCH_BYTE(g_InnSteps, g_MenuStep.sub_step);
}
