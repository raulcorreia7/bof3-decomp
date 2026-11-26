/* Moves the actor's screen y down by 0x20; once it reaches 0 calls ARRIVE, sets step 1 and plays the area SE when no request is pending; then calls DRAW. */
/* AREA_SCREEN_SLIDE_DOWN_STEP (area117 0x801F3024, area119 0x801F3210) */
#define AREA_SCREEN_SLIDE_DOWN_STEP(ARRIVE, DRAW)         \
    u16 position;                                         \
    position              = SELF(Actor)->screen_y + 0x20; \
    SELF(Actor)->screen_y = position;                     \
    if ((s16)position >= 0) {                             \
        ARRIVE();                                         \
        if (SELF(Actor)->header.step == 2) {              \
            return;                                       \
        }                                                 \
        SELF(Actor)->header.step = 1;                     \
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {      \
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));   \
        }                                                 \
    }                                                     \
    DRAW();
