#include "shop_00.h"

/* Handler table dispatched by the shop state counter. */

MATCH void func_801D3AA8(void) {
    SYS_DISPATCH_BYTE(g_ShopStep3Sub1Funcs, g_MenuStep.state);
}
