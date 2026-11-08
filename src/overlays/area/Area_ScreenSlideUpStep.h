/* Moves the actor's screen y up by 0x20 and advances the step once it passes -0xFF, then calls DRAW. A statement
 * macro shared by the area overlays; every change here must verify every member. */
/* AREA_SCREEN_SLIDE_UP_STEP (area117 0x801F2F00, area119 0x801F3114) */
#define AREA_SCREEN_SLIDE_UP_STEP(DRAW)                         \
    u8* work;                                                   \
    work                    = (u8*)g_Task;                      \
    FIELD(u16, work, 0x30u) = (FIELD(u16, work, 0x30u) - 0x20); \
    if ((s16)FIELD(u16, work, 0x30u) < -0xFF) {                 \
        work[2]++;                                              \
    }                                                           \
    DRAW();
