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
            panel         = &g_UiPanelTasks[i + 3];
            panel->unk_0A = i;
            panel->pos.vx = MENU_PANEL_HIDDEN_X;
            panel->pos.vy = i * 54 + 62;
            panel->active = 1;
            panel->panel  = 7;
            panel->mode   = 5;
            panel->state  = 2;
            panel->unk_0B = 0;
            panel->unk_0C = 0;
            i++;
        }
    }
    g_UiPanelTasks[8].pos.vx = BATTLE_PARTY_STRIDE;
    g_UiPanelTasks[8].pos.vy = 0x3E;
    g_UiPanelTasks[8].active = 1;
    g_UiPanelTasks[8].panel  = 7;
    g_UiPanelTasks[8].mode   = 7;
    g_UiPanelTasks[8].state  = D_801E6058 != 0 ? 2 : 3;
    g_UiPanelTasks[8].unk_0A = 0;
    g_ShopStockIndex         = 0;
    g_UiPanelTasks[8].unk_0B = g_ShopPricePercent;
    D_80148470               = D_8018E7CC;
    step                     = &g_MenuStep.state;
    (*step)++;
}
