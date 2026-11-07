#include "battle_15.h"

/* D_8014857x stay address views here: a g_MenuPanelTasks[16] view changes the register allocation. */
MATCH void func_800A8360(void) {
    volatile u8* work;
    volatile u8* work_base;
    u8           one;
    u8           eight;

    work_base = g_BattleChoicePanel;
    one       = 1u;
    eight     = 8u;
    /* FAKE: the order lock holds this run in place; without it the match is 87.18%. */
    ORDER_LOCK_BEGIN
        work                = work_base;
        work[0]             = one;
        D_80148572          = one;
        g_BattleChoicePhase = 2u;
        D_8014857D          = 0xFFu;
    ORDER_LOCK_END;
    D_80148574 = -0xAA;
    D_80148571 = eight;
    D_8014857A = 0u;
    D_8014857B = 0u;
    D_8014857C = 0u;
    D_80148579 = 0u;
    D_80148580 = 0;
    D_80148576 = 0x3Fu;
    work += 0x6C;
    *work      = 0u;
    D_801485DD = eight;
    D_801485DE = 0u;
}
