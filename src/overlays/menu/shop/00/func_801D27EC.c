#include "shop_00.h"

/* Handler table dispatched by the shop state counter. */

MATCH void func_801D27EC(void) {
    SYS_DISPATCH_BYTE(g_ShopStep2Sub3Funcs, D_80148652);
}
