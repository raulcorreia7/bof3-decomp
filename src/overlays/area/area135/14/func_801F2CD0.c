#include "area135_14.h"

MATCH void func_801F2CD0(void) {
    Actor* actor;
    s32    value;

    actor                    = SELF(Actor);
    value                    = g_PartyActors[actor->unk_18].range_54.raw;
    actor->timer             = 0;
    actor->range_54.raw      = value;
    SELF(Actor)->header.mode = 1;
}
