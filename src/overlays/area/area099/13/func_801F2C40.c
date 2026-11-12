#include "area099_13.h"

MATCH void func_801F2C40(void) {
    u8 slot;

    if (!(g_Task->direction_08 & 0x1)) {
        g_Task->direction_08 = (g_Task->direction_08 - 1) & 0x7;
    }
    /* FAKE: retail reads SND_PlayCue as void(s32). */
    ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
    Actor_RequestScript(((g_Task->direction_08 - 1) / 2) + 0x42);
    g_Game.current->u.field.flags_118 |= 0x40;
    slot                     = Actor_FindFreeSlot();
    g_Task->param.actor_slot = slot;
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_ActorSlots[g_Task->param.actor_slot].header.flags = 1;
        g_ActorSlots[g_Task->param.actor_slot].type         = 0x1B;
    }
}
