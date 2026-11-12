#include "area193_13.h"

MATCH void func_801F2E38(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_Game.members[0].chr.character_id == CHAR_ID_RYU_ADULT) {
        Game_SetScriptActive();
        g_CurrentActor->unk_7E += 1;
    }
}
