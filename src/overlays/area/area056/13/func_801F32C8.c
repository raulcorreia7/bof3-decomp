#include "area056_13.h"

MATCH void func_801F32C8(void) {
    Actor* actor;
    s16    height;

    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    height                = Area_ReadHeight(g_Task->x.fixed, g_Task->y.fixed);
    actor                 = g_Task;
    actor->z.part.integer = height + 0x7D0;
    actor->unk_04         = 1;
    actor->vx             = 0;
    actor->vy             = 0;
    actor->vz             = 0;
    actor->gravity        = -8;
    g_GameState->unk_122 -= 2;
}
