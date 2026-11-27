#include "game_00.h"

MATCH void func_801BBE98(void) {
    Actor* work;
    Actor* work2;
    /* FAKE: post-call reload must land in a0 for the retail schedule. */
    FAKE_REG(Actor*, ptr, "a0");
    s16 ret;

    Actor_ClearVelocity();

    work                = SELF(Actor);
    work->unk_06        = work->unk_05 - 1;
    work2               = SELF(Actor);
    work->unk_18        = 0;
    work->unk_1C        = 0;
    work->gravity       = 0;
    work2->option_flags = 0;

    work2 = SELF(Actor);
    ret   = Area_HeightRead(work2->pos.x.fixed, work2->pos.y.fixed);

    work                          = SELF(Actor);
    work->tint.bytes.rgb.r        = 0;
    ptr                           = SELF(Actor);
    COORD_INT(work->pos.z)        = ret;
    ptr->tint.bytes.rgb.g         = 0;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->tint.bytes.flags = 2;

    g_Game.current->u.field.counter.value = 3;
    g_Game.current->u.field.mode.value    = 0;
    g_Game.current->u.field.step.value    = 0;

    Script_Select(SELF(Actor)->direction);

    work = SELF(Actor);
    work->header.mode++;
    ACTOR_CLEAR_STEP();
}
