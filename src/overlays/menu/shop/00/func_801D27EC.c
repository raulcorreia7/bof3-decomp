#include "shop_00.h"

/* Step table dispatched by the shop state counter. */

MATCH void func_801D27EC(void) {
    SYS_DISPATCH_BYTE(g_ShopStep2Sub3Steps, g_MenuStep.state);
}
