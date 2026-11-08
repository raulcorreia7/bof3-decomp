#include "shop_00.h"

/* Handler table for the shop's current menu state, indexed by the shared
 * shop-state byte g_MenuStep.sub_step. */

MATCH void func_801D39BC(void) {
    SYS_DISPATCH_BYTE(g_ShopStep3Funcs, g_MenuStep.sub_step);
}
