#include "shop_00.h"

/* Step table dispatched by the shop state counter. */

/* func_801D3AA8 */
MATCH void Menu_RunInnMenu(void) {
    SYS_DISPATCH_BYTE(g_InnMenuSteps, g_MenuStep.state);
}
