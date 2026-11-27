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
    g_SysThreads[1].tail.title_screen.state    = 0u;
    g_SysThreads[1].tail.title_screen.substate = 0u;
    SYS_ClearCurrentThread();

    for (;;) {
        SYS_ThreadWait(1);
        Title_UpdateStartButton();
        s_TitleSteps[g_SysThreads[1].tail.title_screen.state]();
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
    EMI_ArchiveLoad(EMI_SLOT_DEMO);

    while (!EMI_IsReady()) {
        SYS_ThreadWait(1u);
    }

    GFX_PaletteReset();
    g_GfxPalettePending += 1u;
    SND_BGMPlay(BGM_TITLE, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);

    state                   = g_UITitleState;
    g_UITitleFadePhase      = 1u;
    g_UITitleBannerScroll   = 200u;
    g_UITitleBannerAlpha    = 0u;
    g_UITitleChoicePhase    = 0u;
    g_UITitlePrimaryAlpha   = 0u;
    g_UITitleSecondaryAlpha = 0u;
    g_UITitleInputGate      = 1u;
    g_UITitleState          = state + 1u;
}
