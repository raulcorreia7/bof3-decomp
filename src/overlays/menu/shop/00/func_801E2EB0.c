#include "shop_00.h"

MATCH void func_801E2EB0(void) {
    D_801E5DFC[g_MenuCurrentPanel->state]();
    Shop_DrawItems((ShopPanel*)g_MenuCurrentPanel);
}
