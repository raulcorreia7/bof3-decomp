#include "area191_13.h"

MATCH void func_801F3130(void) {
    Actor* work;

    Game_SetScriptActive();
    work = g_CurrentActor;
    work->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    work = g_CurrentActor;
    work->unk_7E++;
    /* FAKE: retail keeps the request stores below the actor store. */
    FAKE_BARRIER();
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0x19;
}
