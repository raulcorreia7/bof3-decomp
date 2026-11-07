#include "shop_00.h"

/* Handler table for the shop's current menu state, indexed by the shared
 * shop-state byte D_80148651. */

MATCH void func_801D39BC(void) {
    SYS_DISPATCH_BYTE(g_ShopStep3Funcs, D_80148651);
}
