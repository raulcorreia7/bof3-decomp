#include "area191_13.h"

MATCH void func_801F3130(void) {
    Actor* work;

    Game_SetScriptActive();
    work = g_CurrentActor;
    work->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
    work = g_CurrentActor;
    work->unk_7E++;
    g_ScenarioState.state_04 = 2;
    g_ScenarioState.step     = 0x19;
}
