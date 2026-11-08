#include "battle_15.h"

/* First byte of g_BattleChoicePanel (0x80148570); the scalar symbol form
 * emits the direct %lo store the original uses. */

/* FAKE: The original keeps &D_801485B8 in $v1 and reaches 0x80148594 as
 * `sb $a0,-36($v1)`; every clean-C spelling (base pointer, derived `latch`
 * pointer, local `one`/`eight` temporaries, statement reorderings, a search
 * over source rewrites) leaves gcc 2.7.2 preferring a different register for the long-lived
 * constant temporaries, so the base is pinned (ladder rung 8, one pin).
 */
MATCH void func_8009B03C(void) {
    /* FAKE: Pin base to $v1; clean C and a rewrite search left this residual */
    FAKE_REG(volatile u8*, head, "v1");
    volatile u8* latch;
    u8*          slot;
    u8           one;
    u8           eight;
    u16          saved_x;
    u16          saved_y;

    head  = &D_801485B8;
    one   = 1;
    eight = 8;

    *head             = one;
    slot              = g_BattleMessageSlot;
    D_801485B9        = eight;
    D_801485BA        = 3;
    g_BattlePanelMode = 2;
    g_BattleItemRow   = 0;
    D_801485C3        = 0xFF;
    D_801485C4        = slot[5];
    D_801485D8        = &s_BattleEquipment[0];
    D_801485BC        = -0xAA;
    D_801485C5        = one;
    D_801485BE        = 0x3F;
    latch             = head - 0x24;
    /* FAKE: block boundary keeps the second store base-relative off the pinned base. */
    FAKE_ORDER_FENCE();
    *latch             = one;
    /* D_80148574 stays an address symbol here: a g_MenuPanelTasks[16] view changes the code. */
    saved_x            = g_MenuPanelTasks[16].pos.x;
    D_80148597         = one;
    saved_y            = g_MenuPanelTasks[16].pos.y;
    D_80148596         = 4;
    D_80148595         = eight;
    D_801485A0         = 0;
    D_8014859E         = 0;
    g_BattleListCursor = 0;
    D_8014859C         = 0;
    D_801485A1         = 0;
    D_8014859D         = 0;

    g_BattleSelectionHead = 0;

    D_80148574 = SCREEN_WIDTH;
    D_80148598 = saved_x;
    D_8014859A = saved_y;
    D_80148656 = slot[5];
}
