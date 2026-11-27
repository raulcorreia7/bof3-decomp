#include "game_01.h"

/* The handler counts down the frontend timer. At zero, it selects fade phase
 * `3`, opens the window phase, rearms 900 ticks, and advances the state.
 */
/* func_801D0D94 */
MATCH void Title_AdvanceFade(void) { /* func_801D0D94 */
    u16* timer_ptr;
    u16  timer;

    timer_ptr  = &g_SysThreads[1].tail.title_screen.timer;
    timer      = *timer_ptr - 1u;
    *timer_ptr = timer;

    if ((timer << 16) == 0) {
        g_SysThreads[1].tail.title_screen.popup.bytes.fade_phase   = 3u;
        g_SysThreads[1].tail.title_screen.popup.bytes.choice_phase = 1u;
        *timer_ptr                                                 = 900u;
        g_SysThreads[1].tail.title_screen.state                    = g_SysThreads[1].tail.title_screen.state + 1u;
    }
}

/* The handler decrements the local timer. On expiry, it enters local mode
 * `0`, opens selection FX, and advances the title state.
 */
/* func_801D0DF0 */
MATCH void Title_StartFade(void) { /* func_801D0DF0 */
    volatile u16* timer_ptr;
    u16           timer;

    timer_ptr  = &g_SysThreads[1].tail.title_screen.timer;
    timer      = *timer_ptr - 1u;
    *timer_ptr = timer;

    if ((timer << 0x10) == 0) {
        UI_ModeSet(UI_MODE_FADE_OUT);
        SND_StartSelectionEffect();
        g_SysThreads[1].tail.title_screen.state = g_SysThreads[1].tail.title_screen.state + 1u;
    }
}

/* The handler waits for the selection effect to close, resets frontend-local
 * phases and EXE flags, installs the next callback, and advances the state.
 */
/* func_801D0E54 */
MATCH void Title_StartSelectedGame(void) { /* func_801D0E54 */
    if (WINDOW_EFFECT_IDLE()) {
        g_SysThreads[1].tail.title_screen.popup.bytes.fade_phase   = 0u;
        g_SysThreads[1].tail.title_screen.popup.bytes.choice_phase = 0u;
        g_SysThreads[1].tail.title_screen.popup.bytes.input_gate   = 0u;
        SND_StopSelectionEffect();
        SND_SetBankLayout(0u);
        Actor_ClearAll();
        g_PlayClock.thirtieths = 0u;
        g_PlayClock.seconds    = 0u;
        g_PlayClock.minutes    = 0u;
        g_PlayClock.hours      = 0u;
        g_AreaDrawFlags        = 0u;
        Scene_Start(SCENARIO_TITLE);
        SYS_ThreadRegister(0, Game_RunMain);
        g_SysThreads[1].tail.title_screen.state = g_SysThreads[1].tail.title_screen.state + 1u;
    }
}

/* The prompt state returns to state zero when the EXE gate closes. Otherwise,
 * after loading is idle, it reads pad input, starts the selected cue, and
 * advances.
 */
/* func_801D0F00 */
MATCH void Title_WaitInput(void) { /* func_801D0F00 */
    if (g_SysThreads[0].state == 0u) {
        g_UITitleState = 0u;
        return;
    }

    if (EMI_IsReady() && g_SysThreads[2].state == 0u && (g_PadStates[0].pressed & INPUT_ACTION_BUTTONS) != 0u) {
        u8  sel;
        u16 bank;
        g_ScenarioState.state_04 = 1u;
        UI_ModeSet(UI_MODE_SLOW_FADE_OUT);
        sel  = g_SndBGMId;
        bank = D_80143F20;
        SND_BGMFadeOut(sel, bank, 8);
        g_UITitleState = g_UITitleState + 1u;
    }
    Title_DrawChoicePrompt();
}

/* While the EXE gate is active, the handler updates the frontend prompt.
 * Otherwise, it clears the prompt selection and returns the overlay to state
 * zero.
 */
/* func_801D0FB8 */
MATCH void Title_UpdateChoicePrompt(void) { /* func_801D0FB8 */
    if (g_SysThreads[0].state == 0u) {
        g_EmiLoadedCharacterIndex               = 0xFFu;
        g_SysThreads[1].tail.title_screen.state = 0u;
    } else {
        Title_DrawChoicePrompt();
    }
}

/* Closes the current selection FX, restores layout bank 0, installs the
 * alternate frontend callback loop, then exits the active scheduler thread. */
/* func_801D1000 */
MATCH void Title_Leave(void) { /* func_801D1000 */
    if (WINDOW_EFFECT_BUSY()) {
        return;
    }

    SND_StopSelectionEffect();
    SND_SetBankLayout(0u);
    SYS_ThreadRegister(0, Game_RunCampMenu);
    SYS_ThreadExit();
}
