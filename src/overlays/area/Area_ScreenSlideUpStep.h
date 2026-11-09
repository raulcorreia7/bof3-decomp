/* Moves the actor's screen y up by 32 and advances the step once it passes -255, then calls DRAW. A statement
 * macro shared by the area overlays; every change here must verify every member. */
/* AREA_SCREEN_SLIDE_UP_STEP (area117 0x801F2F00, area119 0x801F3114) */
#define AREA_SCREEN_SLIDE_UP_STEP(DRAW)                         \
    g_Task->screen_y -= 32;                                     \
    if ((s16)g_Task->screen_y < -255) {                         \
        g_Task->header.step++;                                  \
    }                                                           \
    DRAW();
