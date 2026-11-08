#include "shop_00.h"

MATCH void func_801D14EC(void) {
    u8  i;
    u8* step;

    if (D_801E6058 != 0) {
        MenuPanelTask* panel;

        /* FAKE: an unset panel live at the loop head fixes retail's temp registers; pure C best 73 differing rows. */
        FAKE_USE(panel);
        i = 0;
        while (i < (u8)Party_CountOrder(PARTY_ORDER_FIELD)) {
            panel             = &g_MenuPanelTasks[i + 3];
            panel->unk_0A     = i;
            LOH(panel->pos.x) = -150;
            panel->pos.y      = i * 54 + 62;
            panel->active     = 1;
            panel->handler    = 7;
            panel->mode       = 5;
            panel->state      = 2;
            panel->unk_0B     = 0;
            panel->unk_0C     = 0;
            i++;
        }
    }
    D_80148454       = BATTLE_PARTY_STRIDE;
    D_80148456       = 0x3E;
    D_80148450       = 1;
    D_80148451       = 7;
    D_80148452       = 7;
    D_80148453       = D_801E6058 != 0 ? 2 : 3;
    D_8014845A       = 0;
    g_ShopStockIndex = 0;
    D_8014845B       = g_ShopPricePercent;
    D_80148470       = D_8018E7CC;
    step             = &D_80148652;
    (*step)++;
}
