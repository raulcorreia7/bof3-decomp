#include "area134_13.h"

MATCH void func_801F331C(void) {
    Actor* actor;
    u8*    work;
    s32    i;

    i    = 0;
    work = SELF(u8);
    SELF_SET(&g_Actors[0]);
    actor = &g_Actors[0];
    do {
        actor->pos.y.fixed += 0x4000;
        i++;
    } while ((u8)i < 2);
    work[1] = 0x12;
    g_Self  = work;
}
