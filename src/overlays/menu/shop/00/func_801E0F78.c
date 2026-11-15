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
    for (count = 0; count < CHARACTER_COUNT; count++) {
        if (g_Characters[count].unk_07 & 1) {
            D_801E6264[D_801E6258++] = count;
        }
    }

    handler     = 7;
    panel_state = 2;
    active      = 1;
    panel_y     = -0x14;

    g_MenuPanelTasks[0].handler = handler;
    g_MenuPanelTasks[0].mode    = 0;
    g_MenuPanelTasks[0].state   = panel_state;
    g_MenuPanelTasks[0].active  = active;
    g_MenuPanelTasks[0].pos.x   = 0x14;
    D_8014835F                  = 0xFF;
    D_80148358                  = 0x70;
    g_MenuPanelTasks[0].pos.y   = panel_y;
    D_8014835A                  = panel_y;
    D_8014833A[0].kind_00       = 0;
    D_80148355                  = handler;
    D_80148356                  = panel_state;
    D_80148357                  = panel_state;
    D_80148354                  = active;
    D_8014835E                  = 4;
    D_80148625                  = handler;
    D_80148626                  = 3;
    D_8014862E                  = 4;
    D_80148624                  = 0;
    if (!(Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) & BYTE_MASK)) {
        D_8014840A = 0x12;
        D_8014840C = BATTLE_PARTY_STRIDE;
        D_80148409 = handler;
        D_8014840B = panel_state;
        D_80148408 = active;
        D_8014840E = 0x26;
    }
}
#else
INCLUDE_ASM(func_801E0F78);
#endif
