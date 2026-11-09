#include "game_01.h"

/* Runs before the main GAME.EMI entry-1 state handler each frame and redirects early start-button transitions into either state 2 or state 7. */
MATCH void UI_HandleStartButton(void) {
    /* The original keeps &g_UiTitleInputGate in s0 and reaches the nearby front-state fields as negative byte offsets off that single base, not as standalone globals. */
    u8*  front_gate = &g_UiTitleInputGate;
    u16* busy       = (u16*)(front_gate - 0xF3);
    u16* state      = (u16*)(front_gate - 0x23);
    u16* timer      = (u16*)(front_gate - 0x13);

    /* FAKE: block boundary after the base setup keeps the field addresses off the gate base. */
    FAKE_ORDER_FENCE();
    if (*front_gate != 0u) {
        if ((g_InputPressed & INPUT_START) != 0u) {
            if (EMI_IsReady()) {
                if (WINDOW_EFFECT_IDLE()) {
                    if (*busy == 0u) {
                        if (*state < 3u) {
                            *timer = 1u;
                            *state = 2u;
                        } else if ((g_UiPopupRequest & WIN_POPUP_PENDING_MASK) == WIN_POPUP_PENDING_OPEN) {
                            UI_SetMode(UI_MODE_FADE_OUT);
                            SND_StartSelectionEffect();
                            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 5));
                            *front_gate = 0u;
                            *state      = 7u;
                        }
                    }
                }
            }
        }
    }
}
