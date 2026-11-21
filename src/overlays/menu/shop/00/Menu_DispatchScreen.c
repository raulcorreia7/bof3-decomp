#include "shop_00.h"

/* Step table dispatched by the shop state counter. */

MATCH void Menu_DispatchScreen(void) {
    SYS_DISPATCH_BYTE(g_MenuScreenSteps, g_MenuStep.step);
}
