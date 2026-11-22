#include "area056_13.h"

MATCH void func_801F32C8(void) {
    Actor* actor;
    s16    height;

    TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    height                  = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    actor                   = TASK(Actor);
    COORD_INT(actor->pos.z) = height + 0x7D0;
    actor->unk_04           = 1;
    setVector(actor, 0, 0, 0);
    actor->gravity = -8;
    g_GameState->u.field.unk_122 -= 2;
}
