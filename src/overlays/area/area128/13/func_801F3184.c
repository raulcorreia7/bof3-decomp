#include "area128_13.h"

MATCH void func_801F3184(void* entity) {
    Actor* actor;

    actor = entity;
    Scene_StartEvent(0x38, 0);
    /* FAKE: preserve the store order. */
    FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}
