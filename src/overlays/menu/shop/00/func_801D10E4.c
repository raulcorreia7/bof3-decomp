#include "shop_00.h"

/* Handler table dispatched by the shop state counter. */

MATCH void func_801D10E4(void) {
    SYS_DISPATCH_BYTE(g_ShopStep2Funcs, D_80148651);
}
