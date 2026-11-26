#include "engine/game/00/game_00.h"

/* func_801B6A04 */
/* Runs the script walk sub-step, then advances the actor's animation. */
MATCH void Party_ScriptWalkRun(void) {
    Actor* work;

    g_Game.current->status.field.flags.unsigned_value |= 4;
    g_PartyScriptWalkSteps[TASK(Actor)->unk_03]();
    work = TASK(Actor);
    if ((work->option_flags & ACTOR_OPT_WAIT_STREAM) == 0) {
        if (work->header.flags & ACTOR_FLAG_STEP_MOVE) {
            Script_AnimStepLoop();
        } else {
            Script_AnimStepOnce();
        }
    }
}
