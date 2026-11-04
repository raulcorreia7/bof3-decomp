#include "area128_13.h"

MATCH void func_801F3184(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    D_801448EB = 0x38;
    D_801448EC = 0;
    /* FAKE: preserve the store order. */
    MATCH_FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}
