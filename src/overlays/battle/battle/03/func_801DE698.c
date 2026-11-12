#include "battle_03.h"

MATCH void func_801DE698(void) {
    BattleEventSlot* work;
    u8*              mask;
    u16              count;

    work = D_801EB4DC;
    if (work->timer != GAME_NONE) {
        mask = &g_Battle.outcome.event_flags;
        *mask |= work->event_type;
        count       = work->timer - 1;
        work->timer = count;
        if (count == 0) {
            work->active = 0;
            *mask &= ~D_801EB4DC->event_type;
            if ((func_801DE858(1) & BYTE_MASK) != 0) {
                g_BattleMessageState = 0;
            }
            return;
        }
    }
    D_801483CA = SP_REF(u8, 0);
}
