#include "shop_00.h"

MATCH void func_801E2DB4(void) {
    D_801E5DF0[g_MenuCurrentPanel->state]();
    Shop_DrawEquipment((s16)g_MenuCurrentPanel->x, (s16)g_MenuCurrentPanel->y,
                       g_CharSlot[D_80144F5A[g_MenuCurrentPanel->unk_0A]]);
}
