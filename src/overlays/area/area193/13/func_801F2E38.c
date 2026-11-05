#include "area193_13.h"

MATCH void func_801F2E38(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (D_80145F09[0][0] == 7) {
        Game_SetScriptActive();
        g_CurrentActor->unk_7E += 1;
    }
}
