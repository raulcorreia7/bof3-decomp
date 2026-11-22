#include "game_01.h"

/* The eight frontend state handlers are indexed by the state byte in
 * Title_Run. The table ends where the glyph geometry records begin. */
static Callback s_TitleSteps[8] = {
    Title_Begin, Title_WaitFade, Title_AdvanceFade, Title_StartFade, Title_StartSelectedGame, Title_WaitInput, Title_UpdateChoicePrompt, Title_Leave,
};

/* Initializes the frontend overlay state, then runs its perpetual input,
 * state-dispatch, and render/update loop. */
/* func_801D0C04 */
MATCH void Title_Run(void) { /* func_801D0C04 */
    g_UiTitleState    = 0u;
    g_UiTitleSubstate = 0u;
    SYS_ClearCurrentThread();

    for (;;) {
        SYS_ThreadWait(1);
        Title_UpdateStartButton();
        s_TitleSteps[g_UiTitleState]();
        Title_UpdateBannerFade();
        Title_UpdateWindowFade();
    }
}

/* Selects layout bank 2, requests DEMO.EMI, waits for the loader, seeds cue
 * 0x8D, then arms the local fade/window state. */
/* func_801D0C90 */
MATCH void Title_Begin(void) { /* func_801D0C90 */
    u16 state;

    SND_SetBankLayout(2u);
    EMI_LoadArchive(EMI_SLOT_DEMO);

    while (!EMI_IsReady()) {
        SYS_ThreadWait(1u);
    }

    GFX_PaletteReset();
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
