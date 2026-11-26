/* Samples the ground under the position projected `steps` frames along the actor velocity, then sets the vertical speed that covers
 * the sampled ground minus the actor z position 224 lower over those frames, and arms the per-actor 16-byte turn record 0 with the
 * frame count and a 64 per-frame delta. */
/* func_801F336C (area095 0x801F336C), func_801F32FC (area096 0x801F32FC) */
#define AREA_STEP_TO_GROUND()                                                           \
    g_ScriptState->steps = 1;                                                           \
    Area_MoveActorRoute(g_ScriptState, 5);                                              \
    steps                         = SELF(Actor)->timer;                                 \
    x                             = SELF(Actor)->pos.x.fixed + SELF(Actor)->vx * steps; \
    y                             = SELF(Actor)->pos.y.fixed + SELF(Actor)->vy * steps; \
    ground                        = Area_HeightSample(x, y);                            \
    work                          = g_Self;                                             \
    floor_height                  = COORD_INT(work->pos.z) - 224;                       \
    work->vz                      = (ground - floor_height) / work->timer;              \
    g_ActorTurnRamps[0].frames_xy = work->timer;                                        \
    g_ActorTurnRamps[0].delta_x   = 64;
