/* Handles Garr's actor or queues an interaction; verify every image after a change. */

s8  PlChar_FindGarrActorSlot(void);
s32 PlChar_FollowerInReach(u8 index);

#define PLCHAR_RUN_GARR_FIELD_TASK(check_actor)                                                                    \
    u8  actor_slot;                                                                                                \
    u8  other_slot;                                                                                                \
    s32 pos_x;                                                                                                     \
    s32 pos_y;                                                                                                     \
    actor_slot = (u8)PlChar_FindGarrActorSlot();                                                                   \
    if (actor_slot != 0xFF) {                                                                                      \
        if ((PlChar_FollowerInReach(actor_slot) & BYTE_MASK) == 0 && (check_actor(actor_slot) & BYTE_MASK) == 0) { \
            g_SpawnedActors[actor_slot].link = 1;                                                                  \
            /* FAKE: retail reads SND_SEPlay as void(s32). */                                                      \
            ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);                                              \
            Script_Request(SELF(Actor)->direction + 8);                                                            \
            g_GameState->u.field.counter.unsigned_value = 2;                                                       \
            g_GameFlags |= 0x1000;                                                                                 \
            Area_RunWalk();                                                                                        \
            SELF(Actor)->timer--;                                                                                  \
            Actor_MovementUpdate();                                                                                \
            g_GameState->u.field.mode.unsigned_value = 1;                                                          \
            SELF(Actor)->header.step++;                                                                            \
            return;                                                                                                \
        }                                                                                                          \
    } else {                                                                                                       \
        pos_x = SELF(Actor)->pos.x.fixed + g_FacingSteps[SELF(Actor)->direction].x * 2;                            \
        pos_y = SELF(Actor)->pos.y.fixed + g_FacingSteps[SELF(Actor)->direction].y * 2;                            \
        if ((g_GameState->status.field.flags.unsigned_value & 0x01) == 0) {                                        \
            other_slot = (u8)Actor_FindInRange(pos_x, pos_y, 1);                                                   \
            if (other_slot != actor_slot) {                                                                        \
                g_Actors[other_slot].interaction_flags |= ACTOR_INTERACTION_PENDING;                               \
            }                                                                                                      \
        }                                                                                                          \
    }                                                                                                              \
    g_GameState->u.field.mode.unsigned_value = 0;
