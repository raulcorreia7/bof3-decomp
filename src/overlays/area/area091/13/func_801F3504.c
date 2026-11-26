#include "area091_13.h"

MATCH void func_801F3504(void) {
    SELF(Actor)->unk_0A -= 1;
    if (SELF(Actor)->unk_0A == 0) {
        g_ScriptVars[3]     = 1;
        SELF(Actor)->unk_04 = 0;
        g_CurrentActor->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
        g_CurrentActor->unk_7E += 1;
        Game_ClearScriptActive();
    }
    func_801F2ED4(SELF(Actor)->unk_0A * 0xA, 0xFF);
}
