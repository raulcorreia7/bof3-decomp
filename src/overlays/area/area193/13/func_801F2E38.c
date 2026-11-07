#include "area193_13.h"

MATCH void func_801F2E38(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_BattlePartyBattlers[0].chr.character_id == 7) {
        Game_SetScriptActive();
        g_CurrentActor->unk_7E += 1;
    }
}
