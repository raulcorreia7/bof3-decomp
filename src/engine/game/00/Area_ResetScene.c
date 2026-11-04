#include "game_00.h"

MATCH void Area_ResetScene(void) {
    Actor* work;

    func_801C3828();
    func_801C3598();
    func_801C329C();
    func_801C2BEC();
    if (!(func_801C3790(0) & BYTE_MASK) && !(func_801C37DC(0) & BYTE_MASK) && !(func_801C2AAC() & BYTE_MASK)) {
        Actor_ClearVelocity();
        g_GameState->counter_11C.s8_value = 3;
        func_801BC000();
        work = SP_REF(void*, 0x44);
        if ((work->unk_0C == 0) && (work->unk_10 == 0) && (work->unk_01 == 1)) {
            work->state_02 = 0;
        }
    }
}
