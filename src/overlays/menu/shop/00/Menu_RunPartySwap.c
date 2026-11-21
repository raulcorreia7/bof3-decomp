#include "shop_00.h"

/* func_801DE188 */
MATCH void Menu_RunPartySwap(void) {
    SYS_DISPATCH_BYTE(g_PartySwapSteps, g_MenuStep.sub_step);
}
