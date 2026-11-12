#include "area062_13.h"

MATCH s32 func_801F2C04(void) {
    Actor* actor;

    actor = g_CurrentActor;
    actor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_Game.members[0].chr.character_id == CHAR_ID_PECO) {
        Game_SetScriptActive();
        actor            = g_CurrentActor;
        g_SceneEventMode = 0x2A;
        g_SceneEventStep = 0;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the unk_7E load below the byte stores. */
        actor->unk_7E += 1;
    }
}
