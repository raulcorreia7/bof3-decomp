#include "area134_13.h"

MATCH void func_801F3B24(void) {
    Actor* actor;
    u8*    work;
    s32    i;

    i    = 0;
    work = SELF(u8);
    SELF_SET(&g_Actors[1]);
    actor = &g_Actors[1];
    do {
        actor->pos.y.fixed += 0x4000;
        i++;
    } while ((u8)i < 2);
    work[1] = 0xE;
    g_Self  = work;
    work[9] = 8;
}
