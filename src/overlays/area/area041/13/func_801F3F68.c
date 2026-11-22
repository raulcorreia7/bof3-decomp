#include "area041_13.h"

MATCH s32 func_801F3F68(void) {
    Actor* actor;
    s32    speed;

    actor = TASK(Actor);
    speed = actor->vx;
    actor->unk_0A -= 1;
    actor->pos.x.fixed += speed;
    if (TASK(Actor)->unk_0A == 0) {
        TASK(Actor)->unk_0A = 8;
        TASK(Actor)->unk_04 = 3;
    }
    g_Game.current->u.field.unk_122 -= 2;
}
