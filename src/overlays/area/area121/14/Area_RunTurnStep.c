#include "area121_14.h"

MATCH void Area_RunTurnStep(void) {
    Actor* actor;
    s32    heading;

    actor   = g_SpadWork;
    heading = actor->unk_6C;
    actor->unk_09--;
    actor->unk_6C = (heading + actor->vz) & 0xFFF;
    if (g_SpadWork->unk_09 == 0) {
        g_SpadWork->unk_01 = 1;
        Area_FinishTurnStep();
    } else {
        func_801F5C7C();
    }
}
