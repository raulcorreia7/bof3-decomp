#include "shop_00.h"

MATCH void func_801E2C18(void) {
    D_801E5DDC[g_MenuCurrentPanel->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    Menu_DrawEquipStatWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                             ((u8*)g_CharSlot)[D_80144F5A[g_MenuCurrentPanel->unk_0A]], g_MenuCurrentPanel->unk_0B,
                             g_MenuCurrentPanel->unk_0C);
}
