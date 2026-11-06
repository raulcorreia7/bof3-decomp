#include "area128_13.h"

MATCH void func_801F3184(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    g_SaveData.scene_event.mode = 0x38;
    g_SaveData.scene_event.step = 0;
    /* FAKE: preserve the store order. */
    MATCH_FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}
