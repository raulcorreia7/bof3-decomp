#include "game_00.h"

/* The slot scanner is entered with a0 still holding the caller's argument, so
 * it is reached through a K&R declaration rather than its typed prototype. */

MATCH void func_801ADAC0(s8 actor_slot) {
    s8 value;

    g_Task->unk_0B = Actor_FindFreeSlot();
    if (g_Task->unk_0B != GAME_NONE) {
        g_ActorSlots[g_Task->unk_0B].header.flags = 1;
        g_ActorSlots[g_Task->unk_0B].type         = 0x19;
        g_ActorSlots[g_Task->unk_0B].unk_06       = actor_slot;
        g_ActorSlots[g_Task->unk_0B].scene_step   = 0;
        value                                     = func_801ADC98();
        g_ActorSlots[g_Task->unk_0B].selection    = value + 0x28;
        g_ActorSlots[g_Task->unk_0B].pos.x.fixed  = g_Task->pos.x.fixed;
        g_ActorSlots[g_Task->unk_0B].pos.y.fixed  = g_Task->pos.y.fixed;
        g_ActorSlots[g_Task->unk_0B].pos.z.fixed  = g_Task->pos.z.fixed;
    }
}
