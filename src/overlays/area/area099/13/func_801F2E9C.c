#define FAKE_DECL_SELF_VOLATILE
#include "area099_13.h"

MATCH void func_801F2E9C(void) {
    Actor* work;

    SELF(Actor)->timer        = 0;
    SELF(Actor)->param.unk_0B = 3;
    SELF(Actor)->unk_0A       = 16 / g_RouteSpeedScale[3];
    work                      = SELF(Actor);
    setVector(work, 0x20000 / (work->unk_0A * 4), -0x18000 / (work->unk_0A * 4), 0x4200);
    SELF(Actor)->unk_0A = 0xE;
    SELF(Actor)->unk_04 = 1;
    g_Game.current->u.field.unk_122 -= 2;
}
