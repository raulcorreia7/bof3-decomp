#include "area062_13.h"

extern u8 D_80145F09;

MATCH s32 func_801F2C04(void) {
    Actor* actor;

    actor = g_CurrentActor;
    actor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (D_80145F09 == 6) {
        Game_SetScriptActive();
        actor      = g_CurrentActor;
        D_801448EB = 0x2A;
        D_801448EC = 0;
        ORDER_FENCE(); /* FAKE: the order fence keeps the unk_7E load below the byte stores. */
        actor->unk_7E += 1;
    }
}
