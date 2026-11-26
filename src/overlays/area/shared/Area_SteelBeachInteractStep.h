/* On the Steel Beach map, when running and the actor in the cell ahead faces the same way, queues that actor's
 * interaction and returns; otherwise turns the actor toward a target through PROBE and, when it finds one, runs the
 * field reset calls, lowers the timer, flags field mode 1 and sets step 1. */
#define AREA_STEEL_BEACH_INTERACT_STEP(PROBE)                                      \
    s32 x;                                                                         \
    s32 y;                                                                         \
    s8  slot;                                                                      \
                                                                                   \
    if (g_GameAreaId != AREA_ID_STEEL_BEACH_MAP) {                                 \
        return;                                                                    \
    }                                                                              \
    x    = TASK(Actor)->pos.x.fixed + g_FacingSteps[TASK(Actor)->direction].x * 2; \
    y    = TASK(Actor)->pos.y.fixed + g_FacingSteps[TASK(Actor)->direction].y * 2; \
    slot = Actor_FindInRange(x, y, 1);                                             \
    if (g_PadStates[0].held & g_InputMasks[FIELD_INPUT_RUN]) {                     \
        if (TASK(Actor)->direction == (g_Actors[(u8)slot].direction & 0x7)) {      \
            g_Actors[(u8)slot].interaction_flags |= ACTOR_INTERACTION_PENDING;     \
            return;                                                                \
        }                                                                          \
    }                                                                              \
    if (PROBE(x, y, (u8)slot) == 0) {                                              \
        return;                                                                    \
    }                                                                              \
    Area_RunWalk();                                                                \
    TASK(Actor)->timer -= 1;                                                       \
    Actor_MovementUpdate();                                                        \
    g_Game.current->u.field.mode.value = 1;                                        \
    TASK(Actor)->header.step           = 1;
