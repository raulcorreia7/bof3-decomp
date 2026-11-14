#include "game_01.h"

/* The eight frontend state handlers are indexed by the state byte in
 * Game_RunFrontend. The table ends where the glyph geometry records begin. */
static Callback s_TitleStates[8] = {
    Game_BeginTitle, Game_WaitTitleFade, Game_AdvanceTitleFade, Game_StartTitleFade, Game_StartSelectedGame, UI_WaitTitleInput, UI_UpdateChoicePrompt, Game_LeaveTitle,
};

/* Initializes the frontend overlay state, then runs its perpetual input,
 * state-dispatch, and render/update loop. */
/* func_801D0C04 */
MATCH void Game_RunTitle(void) { /* func_801D0C04 */
    g_UiTitleState    = 0u;
    g_UiTitleSubstate = 0u;
    func_8014BA04();

    for (;;) {
        SYS_ThreadWait(1);
        UI_HandleStartButton();
        s_TitleStates[g_UiTitleState]();
        UI_UpdateBannerFade();
        UI_UpdateWindowFade();
    }
}

/* Selects layout bank 2, requests DEMO.EMI, waits for the loader, seeds cue
 * 0x8D, then arms the local fade/window state. */
/* func_801D0C90 */
MATCH void Game_BeginTitle(void) { /* func_801D0C90 */
    u16 state;

    SND_SetBankLayout(2u);
    EMI_LoadArchive(EMI_SLOT_DEMO);

    while (!EMI_IsReady()) {
        SYS_ThreadWait(1u);
    }

    GFX_ResetPalette();
    g_GfxPalettePending += 1u;
    SND_PlayBGM(BGM_TITLE, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);

    state                   = g_UiTitleState;
    g_UiTitleFadePhase      = 1u;
    g_UiTitleBannerScroll   = 200u;
    g_UiTitleBannerAlpha    = 0u;
    g_UiTitleChoicePhase    = 0u;
    g_UiTitlePrimaryAlpha   = 0u;
    g_UiTitleSecondaryAlpha = 0u;
    g_UiTitleInputGate      = 1u;
    g_UiTitleState          = state + 1u;
}
