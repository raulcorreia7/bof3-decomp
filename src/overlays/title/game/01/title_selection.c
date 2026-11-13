#include "game_01.h"

/* The handler counts down the frontend timer. At zero, it selects fade phase
 * `3`, opens the window phase, rearms 900 ticks, and advances the state.
 */
/* func_801D0D94 */
MATCH void Game_AdvanceTitleFade(void) { /* func_801D0D94 */
    u16* timer_ptr;
    u16  timer;

    timer_ptr  = &g_UiTitleTimer;
    timer      = *timer_ptr - 1u;
    *timer_ptr = timer;

    if ((timer << 16) == 0) {
        g_UiTitleFadePhase   = 3u;
        g_UiTitleChoicePhase = 1u;
        *timer_ptr           = 900u;
        g_UiTitleState       = g_UiTitleState + 1u;
    }
}

/* The handler decrements the local timer. On expiry, it enters local mode
 * `0`, opens selection FX, and advances the title state.
 */
/* func_801D0DF0 */
MATCH void Game_StartTitleFade(void) { /* func_801D0DF0 */
    volatile u16* timer_ptr;
    u16           timer;

    timer_ptr  = &g_UiTitleTimer;
    timer      = *timer_ptr - 1u;
    *timer_ptr = timer;

    if ((timer << 0x10) == 0) {
        UI_SetMode(UI_MODE_FADE_OUT);
        SND_StartSelectionEffect();
        g_UiTitleState = g_UiTitleState + 1u;
    }
}

/* The handler waits for the selection effect to close, resets frontend-local
 * phases and EXE flags, installs the next callback, and advances the state.
 */
/* func_801D0E54 */
MATCH void Game_StartSelectedGame(void) { /* func_801D0E54 */
    if (WINDOW_EFFECT_IDLE()) {
        g_UiTitleFadePhase   = 0u;
        g_UiTitleChoicePhase = 0u;
        g_UiTitleInputGate   = 0u;
        SND_StopSelectionEffect();
        SND_SetBankLayout(0u);
        Actor_ClearAll();
        g_PlayClock.thirtieths = 0u;
        g_PlayClock.seconds    = 0u;
        g_PlayClock.minutes    = 0u;
        g_PlayClock.hours      = 0u;
        g_AreaDrawFlags        = 0u;
        Scene_Start(16);
        CallbackRegister(0, Game_UpdateMain);
        g_UiTitleState = g_UiTitleState + 1u;
    }
}

/* The prompt state returns to state zero when the EXE gate closes. Otherwise,
 * after loading is idle, it reads pad input, starts the selected cue, and
 * advances.
 */
/* func_801D0F00 */
MATCH void UI_WaitTitleInput(void) { /* func_801D0F00 */
    if (D_80143B40 == 0u) {
        g_UiTitleState = 0u;
        return;
    }

    if (EMI_IsReady() && g_UiWindowEffectBusy == 0u && (g_InputPressed & INPUT_ACTION_BUTTONS) != 0u) {
        u8  sel;
        u16 bank;
        g_SceneState.state_04 = 1u;
        UI_SetMode(UI_MODE_SLOW_FADE_OUT);
        sel  = g_SndBGMId;
        bank = D_80143F20;
        /* FAKE: barrier stages args deferring a2 into slot. */
        FAKE_BARRIER();
        SND_FadeOutBGM(sel, bank, 8);
        g_UiTitleState = g_UiTitleState + 1u;
    }
    UI_DrawChoicePrompt();
}

/* While the EXE gate is active, the handler updates the frontend prompt.
 * Otherwise, it clears the prompt selection and returns the overlay to state
 * zero.
 */
/* func_801D0FB8 */
MATCH void UI_UpdateChoicePrompt(void) { /* func_801D0FB8 */
    if (D_80143B40 == 0u) {
        g_EmiLoadedCharacterIndex = 0xFFu;
        g_UiTitleState            = 0u;
    } else {
        UI_DrawChoicePrompt();
    }
}

/* Closes the current selection FX, restores layout bank 0, installs the
 * alternate frontend callback loop, then exits the active EXE callback thread. */
/* func_801D1000 */
MATCH void Game_LeaveTitle(void) { /* func_801D1000 */
    if (WINDOW_EFFECT_BUSY()) {
        return;
    }

    SND_StopSelectionEffect();
    SND_SetBankLayout(0u);
    CallbackRegister(0, Game_UpdateCampMenu);
    CallbackExit();
}
