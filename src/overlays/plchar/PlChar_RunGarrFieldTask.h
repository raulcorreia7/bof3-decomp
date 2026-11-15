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
            /* FAKE: retail reads SND_PlayCue as void(s32). */                                                     \
            ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);                                                  \
            Actor_RequestScript(g_Task->direction_08 + 8);                                                         \
            g_GameState->u.field.counter_11C.u8_value = 2;                                                         \
            g_GameFlags |= 0x1000;                                                                                 \
            func_801C24D0();                                                                                       \
            g_Task->timer--;                                                                                       \
            Actor_UpdateMovement();                                                                                \
            g_GameState->u.field.mode_12B.u8_value = 1;                                                            \
            g_Task->header.step++;                                                                                 \
            return;                                                                                                \
        }                                                                                                          \
    } else {                                                                                                       \
        pos_x = g_Task->pos.x.fixed + g_FacingSteps[g_Task->direction_08].x * 2;                                   \
        pos_y = g_Task->pos.y.fixed + g_FacingSteps[g_Task->direction_08].y * 2;                                   \
        if ((g_GameState->status.field.flags_12C.u8_value & 0x01) == 0) {                                          \
            other_slot = (u8)Actor_FindInRange(pos_x, pos_y, 1);                                                   \
            if (other_slot != actor_slot) {                                                                        \
                g_Actors[other_slot].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING;                          \
            }                                                                                                      \
        }                                                                                                          \
    }                                                                                                              \
    g_GameState->u.field.mode_12B.u8_value = 0;
