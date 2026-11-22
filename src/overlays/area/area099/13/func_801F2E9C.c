#define FAKE_DECL_TASK_VOLATILE
#include "area099_13.h"

MATCH void func_801F2E9C(void) {
    Actor* work;

    TASK(Actor)->timer        = 0;
    TASK(Actor)->param.unk_0B = 3;
    TASK(Actor)->unk_0A       = 16 / g_RouteSpeedScale[3];
    work                      = TASK(Actor);
    setVector(work, 0x20000 / (work->unk_0A * 4), -0x18000 / (work->unk_0A * 4), 0x4200);
    TASK(Actor)->unk_0A = 0xE;
    TASK(Actor)->unk_04 = 1;
    g_Game.current->u.field.unk_122 -= 2;
}
