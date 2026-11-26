#include "engine/game/00/game_00.h"

/* func_801B9478 */
/* Blinks the actor for eight frames, then returns it to mode 1. */
MATCH void Party_FloorDamageBlink(void) {
    Actor* work;
    Actor* flag_work;
    u8     countdown;

    if (SELF(Actor)->timer != 0) {
        Actor_Move();
        work        = SELF(Actor);
        work->timer = (work->timer - 1);
        if (SELF(Actor)->timer == 0) {
            Actor_ClearVelocity();
        }
    }
    work      = SELF(Actor);
    countdown = work->unk_0A;
    if (countdown != 0) {
        work->unk_0A = (countdown - 1);
        flag_work    = SELF(Actor);
        if (flag_work->unk_0A & 0x1) {
            flag_work->header.flags = (flag_work->header.flags & ~ACTOR_FLAG_HIDDEN);
            return;
        }
        flag_work->header.flags = (flag_work->header.flags | ACTOR_FLAG_HIDDEN);
        return;
    }
    work->header.flags       = (work->header.flags & ~ACTOR_FLAG_HIDDEN);
    SELF(Actor)->header.mode = 1;
    SELF(Actor)->header.step = 0;
    SELF(Actor)->unk_03      = 0;
}
