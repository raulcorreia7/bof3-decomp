#include "area008_13.h"

MATCH void func_801F39BC(void) {
    Actor* s;
    Actor* e;
    s32    index;

    s = &g_Actors[SELF(Actor)->param.unk_0B];
    s->header.flags |= ACTOR_FLAG_HIDDEN;
    s     = SELF(Actor);
    index = s->param.unk_0B;
    e     = &g_Actors[index];
    SELF_SET(e);
    Script_Select(1);
    g_Self = s;
    Actor_Clear();
}
