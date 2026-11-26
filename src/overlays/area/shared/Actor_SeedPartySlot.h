/* Claims a free actor slot for one party member and seeds its row from that member's record: the
 * flags, the actor type, the variant byte, the step, the selection and the screen position. A
 * statement macro, not a function: the early return belongs to the caller's body. Every change
 * must verify every member. */
/* func_801F2E9C, func_801F304C, func_801F31FC, func_801F33AC, func_801F355C, func_801F3708 and
 * func_801F38B4 (area092), func_801FCD14 and func_801FCECC (scena02), func_801FD28C (scena01), func_801FC8A0 (scena05) and
 * func_801FCB80 (scena06), func_801F2C94 and func_801F2E60 (area038) */
#define ACTOR_SEED_PARTY_SLOT(member, table, actor_type, unk06)                                           \
    {                                                                                                     \
        SELF_SET(&g_Game.members[member]);                                                                \
        SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();                                          \
        if (SELF(Actor)->param.actor_slot == GAME_NONE) {                                                 \
            return;                                                                                       \
        }                                                                                                 \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;                                  \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = actor_type;                         \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06       = unk06;                              \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].vx           = 0;                                  \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].selection    = (table)[g_PartyFieldOrder[member]]; \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].screen_x     = SELF(Actor)->screen_x;              \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].screen_y     = SELF(Actor)->screen_y;              \
    }
