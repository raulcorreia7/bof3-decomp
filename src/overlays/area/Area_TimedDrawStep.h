/* Calls DRAW with the timer, counts the timer up and, at 8, restarts it and advances the step. */
/* AREA_TIMED_DRAW_STEP (area102 0x801F3408, area119 0x801F3D90). */
#define AREA_TIMED_DRAW_STEP(DRAW) \
    DRAW(g_Task->timer);           \
    g_Task->timer += 1;            \
    if (g_Task->timer >= 8U) {     \
        g_Task->timer = 0;         \
        g_Task->header.step += 1;  \
    }
