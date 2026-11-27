#include "shop_00.h"

MATCH void func_801E0F78(void) {
    u8 count;

    D_801E6258 = 0;
    for (count = 0; count < CHAR_INDEX_COUNT; count++) {
        if (g_Characters[count].party_flags & PARTY_FLAG_JOINED) {
            D_801E6264[D_801E6258++] = count;
        }
    }

    g_UiPanelTasks[0].panel   = 7;
    g_UiPanelTasks[0].mode    = 0;
    g_UiPanelTasks[0].state   = 2;
    g_UiPanelTasks[0].active  = 1;
    g_UiPanelTasks[0].unk_0A  = 0;
    g_UiPanelTasks[0].pos.vx  = 0x14;
    g_UiPanelTasks[0].pos.vy  = -0x14;
    g_UiPanelTasks[1].panel   = 7;
    g_UiPanelTasks[1].mode    = 2;
    g_UiPanelTasks[1].state   = 2;
    g_UiPanelTasks[1].active  = 1;
    g_UiPanelTasks[1].unk_0A  = 4;
    g_UiPanelTasks[1].unk_0B  = 0xFF;
    g_UiPanelTasks[1].pos.vx  = 0x70;
    g_UiPanelTasks[1].pos.vy  = -0x14;
    g_UiPanelTasks[21].panel  = 7;
    g_UiPanelTasks[21].mode   = 3;
    g_UiPanelTasks[21].unk_0A = 4;
    g_UiPanelTasks[21].active = 0;
    if (!(Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) & BYTE_MASK)) {
        g_UiPanelTasks[6].panel  = 7;
        g_UiPanelTasks[6].mode   = 0x12;
        g_UiPanelTasks[6].state  = 2;
        g_UiPanelTasks[6].active = 1;
        g_UiPanelTasks[6].pos.vx = BATTLE_PARTY_STRIDE;
        g_UiPanelTasks[6].pos.vy = 0x26;
    }
}
