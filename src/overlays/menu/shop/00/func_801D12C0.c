#include "shop_00.h"

/* Handler table dispatched by the shop state counter. */

MATCH void func_801D12C0(void) {
    SYS_DISPATCH_BYTE(g_ShopStep2Sub1Funcs, g_MenuStep.state);
}
