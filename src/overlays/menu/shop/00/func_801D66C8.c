#include "shop_00.h"

MATCH void func_801D66C8(void) {
    if (g_UiWindowChannel & FRONTEND_FLAG_CONFIRM) {
        g_MenuStep.step     = 1;
        g_MenuStep.sub_step = 0;
    }
}
