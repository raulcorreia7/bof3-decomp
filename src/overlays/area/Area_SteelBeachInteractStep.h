/* On the Steel Beach map, when running and the actor in the cell ahead faces the same way, queues that actor's
 * interaction and returns; otherwise turns the actor toward a target through PROBE and, when it finds one, runs the
 * field reset calls, lowers the timer, flags field mode 1 and sets step 1. */
#define AREA_STEEL_BEACH_INTERACT_STEP(PROBE)                                       \
    s32 x;                                                                          \
    s32 y;                                                                          \
    s8  slot;                                                                       \
                                                                                    \
    if (g_GameAreaId != AREA_ID_STEEL_BEACH_MAP) {                                  \
        return;                                                                     \
    }                                                                               \
    x    = g_Task->pos.x.fixed + g_FacingSteps[g_Task->direction_08].x * 2;         \
    y    = g_Task->pos.y.fixed + g_FacingStepY[g_Task->direction_08 * 2] * 2;       \
    slot = Actor_FindInRange(x, y, 1);                                              \
    if (g_InputHeld & g_InputMasks[FIELD_INPUT_RUN]) {                              \
        if (g_Task->direction_08 == (g_Actors[(u8)slot].direction_08 & 0x7)) {      \
            g_Actors[(u8)slot].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING; \
            return;                                                                 \
        }                                                                           \
    }                                                                               \
    if (PROBE(x, y, (u8)slot) == 0) {                                               \
        return;                                                                     \
    }                                                                               \
    func_801C24D0();                                                                \
    g_Task->timer -= 1;                                                             \
    Actor_UpdateMovement();                                                         \
    g_Game.current->u.field.mode_12B.s8_value = 1;                                  \
    g_Task->header.step                       = 1;
