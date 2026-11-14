/* Claims a free actor slot for one party member and seeds its row from that member's record: the
 * flags, the actor type, the variant byte, the step, the selection and the screen position. A
 * statement macro, not a function: the early return belongs to the caller's body. Every change
 * must verify every member. */
/* func_801F2E9C, func_801F304C, func_801F31FC, func_801F33AC, func_801F355C, func_801F3708 and
 * func_801F38B4 (area092) */
#define ACTOR_SEED_PARTY_SLOT(member, table, unk06)                                               \
    {                                                                                             \
        TASK_SET(&g_Game.members[member]);                                                        \
        g_Task->param.actor_slot = Actor_FindFreeSlot();                                          \
        if (g_Task->param.actor_slot == GAME_NONE) {                                              \
            return;                                                                               \
        }                                                                                         \
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;                                  \
        g_SpawnedActors[g_Task->param.actor_slot].type         = 6;                                  \
        g_SpawnedActors[g_Task->param.actor_slot].unk_06       = unk06;                              \
        g_SpawnedActors[g_Task->param.actor_slot].scene_step   = 0;                                  \
        g_SpawnedActors[g_Task->param.actor_slot].selection    = (table)[g_PartyFieldOrder[member]]; \
        g_SpawnedActors[g_Task->param.actor_slot].unk_2E       = g_Task->screen_x;                   \
        g_SpawnedActors[g_Task->param.actor_slot].unk_30       = g_Task->screen_y;                   \
    }
