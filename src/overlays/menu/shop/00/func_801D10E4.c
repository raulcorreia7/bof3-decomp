#include "shop_00.h"

/* Step table dispatched by the shop state counter. */

MATCH void func_801D10E4(void) {
    SYS_DISPATCH_BYTE(g_ShopStep2Steps, g_MenuStep.sub_step);
}
