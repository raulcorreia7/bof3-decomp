#include "area092_13.h"

/* Give the third party member a field actor: claim a free slot and seed its row from the member. */
MATCH void func_801F38B4(void) {
    TASK_SET(&g_Game.members[2]);
    g_Task->param.actor_slot = Actor_FindFreeSlot();
    if (g_Task->param.actor_slot == 0xFF) {
        return;
    }

    g_ActorSlots[g_Task->param.actor_slot].header.flags = 1;
    g_ActorSlots[g_Task->param.actor_slot].type         = 6;
    g_ActorSlots[g_Task->param.actor_slot].unk_06       = 1;
    g_ActorSlots[g_Task->param.actor_slot].scene_step   = 0;
    g_ActorSlots[g_Task->param.actor_slot].selection    = D_801F3A90[g_PartyFieldOrder[2]];
    g_ActorSlots[g_Task->param.actor_slot].unk_2E       = g_Task->screen_x;
    g_ActorSlots[g_Task->param.actor_slot].unk_30       = g_Task->screen_y;
}
