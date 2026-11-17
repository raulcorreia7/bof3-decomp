#include "shop_00.h"

/* Step table dispatched by the shop state counter. */

MATCH void Shop_DispatchStep(void) {
    SYS_DISPATCH_BYTE(g_ShopSteps, g_MenuStep.step);
}
