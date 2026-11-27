#include "area041_13.h"

MATCH s32 func_801F3F68(void) {
    Actor* actor;
    s32    speed;

    actor = SELF(Actor);
    speed = actor->vx;
    actor->unk_0A -= 1;
    actor->pos.x.fixed += speed;
    if (SELF(Actor)->unk_0A == 0) {
        SELF(Actor)->unk_0A = 8;
        SELF(Actor)->unk_04 = 3;
    }
    g_Game.current->u.field.unk_122 -= 2;
}
