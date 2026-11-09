/* Moves the actor's screen y down by 0x20; once it reaches 0 calls ARRIVE, sets step 1 and plays the area cue when no
 * request is pending; then calls DRAW. A statement macro shared by the area overlays; every change here must verify
 * every member. */
/* AREA_SCREEN_SLIDE_DOWN_STEP (area117 0x801F3024, area119 0x801F3210) */
#define AREA_SCREEN_SLIDE_DOWN_STEP(ARRIVE, DRAW)         \
    u16 position;                                         \
    position         = g_Task->screen_y + 0x20;           \
    g_Task->screen_y = position;                          \
    if ((s16)position >= 0) {                             \
        ARRIVE();                                         \
        if (g_Task->header.step == 2) {                   \
            return;                                       \
        }                                                 \
        g_Task->header.step = 1;                          \
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {      \
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01)); \
        }                                                 \
    }                                                     \
    DRAW();
