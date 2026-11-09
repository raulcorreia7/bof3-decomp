#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E0F78(void) {
    u8 i;
    u8 count;

    D_801E6258 = 0;
    for (count = 0; count < CHARACTER_COUNT; count++) {
        if (g_Characters[count].unk_07 & 1) {
            D_801E6264[D_801E6258++] = count;
        }
    }
    g_MenuPanelTasks[0].handler = 7;
    D_80148332                  = 0;
    g_MenuPanelTasks[0].state   = 2;
    g_MenuPanelTasks[0].active  = 1;
    D_80148334                  = 0x14;
    D_8014835F                  = 0xFF;
    D_80148358                  = 0x70;
    D_80148336                  = -0x14;
    D_8014835A                  = -0x14;
    D_8014833A[0].kind_00       = 0;
    D_80148355                  = 7;
    D_80148356                  = 2;
    D_80148357                  = 2;
    D_80148354                  = 1;
    D_8014835E                  = 4;
    D_80148625                  = 7;
    D_80148626                  = 3;
    D_8014862E                  = 4;
    D_80148624                  = 0;
    if (!(Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) & BYTE_MASK)) {
        D_8014840A = 0x12;
        D_8014840C = BATTLE_PARTY_STRIDE;
        D_80148409 = 7;
        D_8014840B = 2;
        D_80148408 = 1;
        D_8014840E = 0x26;
    }
}
#else
INCLUDE_ASM(func_801E0F78);
#endif
