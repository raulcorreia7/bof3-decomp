#include "area135_14.h"

MATCH void func_801F2CD0(void) {
    Actor* actor;
    s32    value;

    actor                    = TASK(Actor);
    value                    = *(s32*)(D_80147AAC + actor->unk_18 * ACTOR_SIZE);
    actor->timer             = 0;
    actor->range_54.raw      = value;
    TASK(Actor)->header.mode = 1;
}
