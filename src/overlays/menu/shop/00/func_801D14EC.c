#include "shop_00.h"

/* nonmatching unmeasured: tried untested-head loop (call in the test), store orders, base+index operand order, u32
 * index copies, an s16 view of x (+1.2, li -0x96). resume: MenuPanelTask.x as s16 (shared type change) and a register
 * choice that keeps the 8i temp in a0, so the loop-exit delay slot stays nop. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D14EC(void) {
    MenuPanelTask* panel;
    u8             i;
    u8*            step;

    if (D_801E6058 != 0) {
        i = 0;
        while (i < (u8)Party_CountOrder(0)) {
            panel            = &g_MenuPanelTasks[i + 3];
            panel->y         = i * 54 + 62;
            panel->unk_0A    = i;
            panel->x         = -150;
            panel->unk_00[0] = 1;
            panel->unk_00[1] = 7;
            panel->unk_00[2] = 5;
            panel->state     = 2;
            panel->unk_0B    = 0;
            panel->unk_0C    = 0;
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
#else
INCLUDE_ASM(func_801D14EC);
#endif
