/* Samples the ground under the position projected `steps` frames along the actor velocity, then sets the vertical speed that covers
 * the sampled ground minus the actor z position 224 lower over those frames, and arms the per-actor 16-byte turn record 0 with the
 * frame count and a 64 per-frame delta. */
/* func_801F336C (area095 0x801F336C), func_801F32FC (area096 0x801F32FC) */
#define AREA_STEP_TO_GROUND()                                 \
    g_ScriptState->unk_07 = 1;                                \
    Area_MoveActorRoute(g_ScriptState, 5);                    \
    steps         = g_Task->timer;                            \
    x             = g_Task->pos.x.fixed + g_Task->vx * steps; \
    y             = g_Task->pos.y.fixed + g_Task->vy * steps; \
    ground        = Area_SampleHeight(x, y);                  \
    work          = g_Task;                                   \
    floor_height  = COORD_INT(work->pos.z) - 224;             \
    work->vz      = (ground - floor_height) / work->timer;    \
    D_80147CB9[0] = work->timer;                              \
    D_80147CBC[0] = 64;
