#include "area041_13.h"
#include "area/spad.h"

MATCH s32 func_801F3F68(void) {
    Actor* actor;
    s32    speed;

    actor = g_Task;
    speed = actor->vx;
    actor->unk_0A -= 1;
    actor->pos.x.fixed += speed;
    if (g_Task->unk_0A == 0) {
        g_Task->unk_0A = 8;
        g_Task->unk_04 = 3;
    }
    g_Game.current->u.field.unk_122 -= 2;
}
