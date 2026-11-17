#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E0F78(void) {
    u8  i;
    u8  count;
    s32 handler;
    s32 panel_state;
    s32 active;
    s32 panel_y;

    D_801E6258 = 0;
    for (count = 0; count < CHAR_INDEX_COUNT; count++) {
        if (g_Characters[count].party_flags & PARTY_FLAG_JOINED) {
            D_801E6264[D_801E6258++] = count;
        }
    }

    handler     = 7;
    panel_state = 2;
    active      = 1;
    panel_y     = -0x14;

    g_MenuPanelTasks[0].panel   = handler;
    g_MenuPanelTasks[0].mode    = 0;
    g_MenuPanelTasks[0].state   = panel_state;
    g_MenuPanelTasks[0].active  = active;
    g_MenuPanelTasks[0].pos.x   = 0x14;
    g_MenuPanelTasks[1].unk_0B  = 0xFF;
    g_MenuPanelTasks[1].pos.x   = 0x70;
    g_MenuPanelTasks[0].pos.y   = panel_y;
    g_MenuPanelTasks[1].pos.y   = panel_y;
    D_8014833A[0].type          = 0;
    g_MenuPanelTasks[1].panel   = handler;
    g_MenuPanelTasks[1].mode    = panel_state;
    g_MenuPanelTasks[1].state   = panel_state;
    g_MenuPanelTasks[1].active  = active;
    g_MenuPanelTasks[1].unk_0A  = 4;
    g_MenuPanelTasks[21].panel  = handler;
    g_MenuPanelTasks[21].mode   = 3;
    g_MenuPanelTasks[21].unk_0A = 4;
    g_MenuPanelTasks[21].active = 0;
    if (!(Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) & BYTE_MASK)) {
        g_MenuPanelTasks[6].mode   = 0x12;
        g_MenuPanelTasks[6].pos.x  = BATTLE_PARTY_STRIDE;
        g_MenuPanelTasks[6].panel  = handler;
        g_MenuPanelTasks[6].state  = panel_state;
        g_MenuPanelTasks[6].active = active;
        g_MenuPanelTasks[6].pos.y  = 0x26;
    }
}
#else
INCLUDE_ASM(func_801E0F78);
#endif
