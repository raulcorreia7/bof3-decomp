#include "area191_13.h"

MATCH void func_801F3130(void) {
    Actor* work;

    Game_SetScriptActive();
    work = g_CurrentActor;
    work->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
    work = g_CurrentActor;
    work->unk_7E++;
    /* FAKE: retail keeps the request stores below the actor store. */
    MATCH_FAKE_BARRIER();
    D_80146874 = 2;
    D_80146875 = 0x19;
}
