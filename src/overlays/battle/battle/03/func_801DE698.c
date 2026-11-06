#include "battle_03.h"

MATCH void func_801DE698(void) {
    BattleEventSlot* work;
    u8*              mask;
    u16              count;

    work = D_801EB4DC;
    if (work->unk_08 != GAME_NONE) {
        mask = &g_BattleEventFlags;
        *mask |= work->unk_01;
        count        = work->unk_08 - 1;
        work->unk_08 = count;
        if (count == 0) {
            work->unk_00 = 0;
            *mask &= ~D_801EB4DC->unk_01;
            if ((func_801DE858(1) & 0xFF) != 0) {
                g_BattleMessageState = 0;
            }
            return;
        }
    }
    D_801483CA = SP_REF(u8, 0);
}
