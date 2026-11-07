#include "battle_03.h"

/* primes the active work area's sprite kind, counts the shared panel
 * timer down and raises its pending bit on expiry, then queues the work area's
 * step and closes the sequence.
 */
MATCH void func_801E51DC(void) {
    volatile u8* timer;
    u8           count;

    Battle_CancelTurn(g_Task->slot);
    timer  = &g_BattleLivingEnemyCount;
    count  = *timer - 1;
    *timer = count;
    if ((count & BYTE_MASK) == 0) {
        g_BattleResult |= BATTLE_RESULT_VICTORY;
    }
    GFX_FreePaletteFadeTarget((void*)g_Task);
    Battle_ClearSlotPending(g_Task->slot);
    g_BattleMessageState = 2;
    func_801DE804();
    func_800ACFF4();
}
