/* Moves the actor's screen y up by 32 and advances the step once it passes -255, then calls DRAW. */
/* AREA_SCREEN_SLIDE_UP_STEP (area117 0x801F2F00, area119 0x801F3114) */
#define AREA_SCREEN_SLIDE_UP_STEP(DRAW)      \
    TASK(Actor)->screen_y -= 32;             \
    if ((s16)TASK(Actor)->screen_y < -255) { \
        TASK(Actor)->header.step++;          \
    }                                        \
    DRAW();
