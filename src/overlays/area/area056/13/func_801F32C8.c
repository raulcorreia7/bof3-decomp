#include "area056_13.h"

MATCH void func_801F32C8(void) {
    Actor* actor;
    s16    height;

    g_SpadWork->flags_00 &= 0xBF;
    height                = Area_ReadHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    actor                 = g_SpadWork;
    actor->z.part.integer = height + 0x7D0;
    actor->unk_04         = 1;
    actor->unk_0C         = 0;
    actor->unk_10         = 0;
    actor->vz             = 0;
    actor->gravity        = -8;
    g_GameState->unk_122 -= 2;
}
