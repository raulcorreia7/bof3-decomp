#include "battle_15.h"

/* D_80148572, D_8014857D and D_80148574 stay address symbols: a g_UiPanelTasks[16] view changes the code. */
MATCH void func_800A8360(void) {
    volatile u8* work;
    volatile u8* work_base;
    u8           one;
    u8           eight;

    work_base = g_BattleChoicePanel;
    one       = 1u;
    eight     = 8u;
    /* FAKE: the block holds this run in place; without it the match is 87.18%. */
    do {
        work                = work_base;
        work[0]             = one;
        D_80148572          = one;
        g_BattleChoicePhase = 2u;
        D_8014857D          = 0xFFu;
    } while (0);
    D_80148574                      = -0xAA;
    g_UiPanelTasks[16].panel        = eight;
    g_UiPanelTasks[16].unk_0A       = 0u;
    g_UiPanelTasks[16].unk_0B       = 0u;
    g_UiPanelTasks[16].unk_0C       = 0u;
    g_UiPanelTasks[16].unk_09       = 0u;
    g_UiPanelTasks[16].u.message.id = 0;
    g_UiPanelTasks[16].pos.vy       = 63u;
    work += 0x6C;
    *work      = 0u;
    D_801485DD = eight;
    D_801485DE = 0u;
}
