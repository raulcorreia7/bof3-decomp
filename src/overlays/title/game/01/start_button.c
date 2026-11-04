#include "game_01.h"

/* Runs before the main GAME.EMI entry-1 state handler each frame and redirects
 * early start-button transitions into either state 2 or state 7. */
MATCH void UI_HandleStartButton(void) {
    /* The original keeps &g_UiTitleInputGate in s0 and reaches the nearby
     * front-state fields as negative byte offsets off that single base, not as
     * standalone globals:
     *   D_80143B40       (0x80143B40) = lhu -0xF3(s0)
     *   g_UiTitleState (0x80143C10) = lhu/sh -0x23(s0)
     *   g_UiTitleTimer (0x80143C20) = sh -0x13(s0)
     * EFFECT_BUSY, INPUT_State and POPUP_WORD are genuine standalone globals (each
     * its own `lui`) and stay declared as such. */
    u8*  front_gate = &g_UiTitleInputGate;
    u16* busy       = (u16*)(front_gate - 0xF3);
    u16* state      = (u16*)(front_gate - 0x23);
    u16* timer      = (u16*)(front_gate - 0x13);

    /* FAKE: block boundary after the base setup keeps the field addresses off the gate base. */
    ORDER_LOCK((void)0);
    if (*front_gate != 0u) {
        if ((g_InputPressed & INPUT_START) != 0u) {
            if (EMI_LoaderIsReady()) {
                if (WINDOW_EFFECT_IDLE()) {
                    if (*busy == 0u) {
                        if (*state < 3u) {
                            *timer = 1u;
                            *state = 2u;
                        } else if ((g_UiPopupRequest & WIN_POPUP_PENDING_MASK) == WIN_POPUP_PENDING_OPEN) {
                            UI_SetMode(0);
                            SND_StartSelectionEffect();
                            SND_PlayCue(EMI_CUE_ID(1, 5));
                            *front_gate = 0u;
                            *state      = 7u;
                        }
                    }
                }
            }
        }
    }
}
