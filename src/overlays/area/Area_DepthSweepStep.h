/* Calls DRAW with the actor's depth and the upper bits of its counter (0x0B), steps the counter down by 2 and the
 * depth up by 1, and clears the actor once the depth reaches -0xBF. A statement macro shared by the area overlays;
 * every change here must verify every member. */
/* AREA_DEPTH_SWEEP_STEP (area095 0x801F2EC0, area096 0x801F2E50) */
#define AREA_DEPTH_SWEEP_STEP(DRAW)                         \
    Actor* work;                                            \
    DRAW(g_Task->pos.z.fixed, g_Task->param.unk_0B & 0xF8); \
    work = g_Task;                                          \
    work->param.unk_0B -= 2;                                \
    work->pos.z.fixed += 1;                                 \
    if (g_Task->pos.z.fixed >= -0xBF) {                     \
        Actor_Clear();                                      \
    }
