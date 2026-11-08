#include "shop_00.h"

/* Lists the party members whose record flag bit 0 is set into D_801E6264, then builds the shop's first two panel
 * tasks (and slot 6 when Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) is clear).
 * nonmatching 86.53%: retail keeps &D_80148331 in v0 and stores the slot-0 bytes through it before the other
 * fields, in source order; ours folds the pointer to absolute stores and schedules them later. A MenuPanelTask
 * view gives the same score. resume: a pointer GCC cannot fold. */
/* nonmatching unmeasured: tried local u8 pointer (folds to absolute), panel-task struct views of the slot-0 bytes with
 * the -fno-rerun-cse-after-loop row, all 24 orders of the slot-0 stores (92.66 only with the stores out of order),
 * chained -0x14/2 stores. resume: a shape that gives 7 the s0 home and keeps -0x14 in a0 while the slot-0 stores stay
 * in retail order. */
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
    g_MenuPanelTasks[0].unk_00[1] = 7;
    D_80148332                    = 0;
    g_MenuPanelTasks[0].state     = 2;
    g_MenuPanelTasks[0].unk_00[0] = 1;
    D_80148334                    = 0x14;
    D_8014835F                    = 0xFF;
    D_80148358                    = 0x70;
    D_80148336                    = -0x14;
    D_8014835A                    = -0x14;
    D_8014833A[0].kind_00         = 0;
    D_80148355                    = 7;
    D_80148356                    = 2;
    D_80148357                    = 2;
    D_80148354                    = 1;
    D_8014835E                    = 4;
    D_80148625                    = 7;
    D_80148626                    = 3;
    D_8014862E                    = 4;
    D_80148624                    = 0;
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
