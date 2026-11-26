/* Calls DRAW with the timer, counts the timer up and, at 8, restarts it and advances the step. */
/* AREA_TIMED_DRAW_STEP (area102 0x801F3408, area119 0x801F3D90) */
#define AREA_TIMED_DRAW_STEP(DRAW)     \
    DRAW(SELF(Actor)->timer);          \
    SELF(Actor)->timer += 1;           \
    if (SELF(Actor)->timer >= 8U) {    \
        SELF(Actor)->timer = 0;        \
        SELF(Actor)->header.step += 1; \
    }
