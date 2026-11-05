#include "area049_14.h"

MATCH void func_801F360C(void) {
    ActorSlot* actor_slot;
    s32        actor_index;

    if (D_80145F09 == 5) {
        actor_index = func_8019601C() & 0xFF;
        if (actor_index != 0xFF) {
            actor_slot           = &g_ActorSlots[actor_index];
            actor_slot->flags_00 = ACTOR_FLAG_IN_USE;
            actor_slot->type     = 0x6C;
        }
        SND_PlayCue(0x209U);
        g_CurrentActor->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
        func_801A4BC0(0xB, 0x55, 0xC0);
        func_801A4BC0(0xC, 0x55, 0xC0);
        D_80146874    = 4;
        *g_ScriptVars = 0;
        D_80146875    = 0x1E;
        return;
    }
    g_CurrentActor->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
}
