#include "area104_14.h"

MATCH void Area_RunTurnStep(void) {
    Actor* work = g_SpadWork;
    s32 heading = work->unk_6C;
    u8 timer = work->unk_09 - 1;
    s32 speed = work->vz;

    work->unk_09 = timer;
    work->unk_6C = (heading + speed) & 0xFFF;
    if (g_SpadWork->unk_09 == 0) {
        g_SpadWork->unk_01 = 1;
        Area_FinishTurnStep();
    } else {
        func_801F5738();
    }
}
