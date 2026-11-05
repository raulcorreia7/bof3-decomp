#include "area008_13.h"

MATCH void func_801F39BC(void) {
    Actor* s;
    Actor* e;
    s32    idx;

    s = (Actor*)&g_Actors[((u8*)g_SpadWork)[0x0B]];
    s->flags_00 |= ACTOR_FLAG_HIDDEN;
    s          = g_SpadWork;
    idx        = ((u8*)s)[0x0B];
    e          = &g_Actors[idx];
    g_SpadWork = (Actor*)e;
    Actor_SelectScript(1);
    g_SpadWork = s;
    Actor_Clear();
}
