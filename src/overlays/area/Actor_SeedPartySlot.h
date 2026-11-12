#ifndef AREA_ACTOR_SEED_PARTY_SLOT_H
#define AREA_ACTOR_SEED_PARTY_SLOT_H

/* Claim a free actor slot for one party member and seed its row from the member's record.
 * A statement macro: it is the whole function body, early return included. */
#define ACTOR_SEED_PARTY_SLOT(member, table, unk06)                                               \
    {                                                                                             \
        TASK_SET(&g_Game.members[member]);                                                        \
        g_Task->param.actor_slot = Actor_FindFreeSlot();                                          \
        if (g_Task->param.actor_slot == GAME_NONE) {                                              \
            return;                                                                               \
        }                                                                                         \
        g_ActorSlots[g_Task->param.actor_slot].header.flags = 1;                                  \
        g_ActorSlots[g_Task->param.actor_slot].type         = 6;                                  \
        g_ActorSlots[g_Task->param.actor_slot].unk_06       = unk06;                              \
        g_ActorSlots[g_Task->param.actor_slot].scene_step   = 0;                                  \
        g_ActorSlots[g_Task->param.actor_slot].selection    = (table)[g_PartyFieldOrder[member]]; \
        g_ActorSlots[g_Task->param.actor_slot].unk_2E       = g_Task->screen_x;                   \
        g_ActorSlots[g_Task->param.actor_slot].unk_30       = g_Task->screen_y;                   \
    }

#endif
