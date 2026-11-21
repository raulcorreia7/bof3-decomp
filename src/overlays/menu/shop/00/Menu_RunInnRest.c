#include "shop_00.h"

/* Step table dispatched by the shop state counter. */

/* func_801D41B0 */
MATCH void Menu_RunInnRest(void) {
    SYS_DISPATCH_BYTE(g_InnRestSteps, g_MenuStep.state);
}
