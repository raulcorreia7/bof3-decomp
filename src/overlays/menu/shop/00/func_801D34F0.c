#include "shop_00.h"

/* Handler table dispatched by the shop state counter. */

MATCH void func_801D34F0(void) {
    SYS_DISPATCH_BYTE(g_ShopStep8Sub2Funcs, D_80148652);
}
