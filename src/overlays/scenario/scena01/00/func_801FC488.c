#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FC488(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 3;
            SND_StopSequence(0, 0);
            SND_PlayBGM(0x11, 0x64, 8);
            g_AreaDrawFlags = 0;
            g_GameFlags |= 0x80;
            Message_StartAreaMessage(0x10);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 4;
                SYS_SetFlag(g_SceneFlags, 0x3E);
                Game_RequestAreaChange(AREA_ID_FARM, TO_COORD(8), TO_COORD(83), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 7) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.flags_01 |= 1;
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 7;
                FAKE_BARRIER(); /* FAKE: retail stores the flag byte before the call, not in its delay slot. */
                func_80153DE8();
                g_ScriptVars[0] = 8;
                Message_StartAreaMessage(0x1C);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
            }
            break;
        case 7:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(UI_MODE_LONG_FADE_IN);
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_SceneState.step_05 = 8;
            }
            break;
        case 8:
            if (WINDOW_EFFECT_IDLE()) {
                g_ScriptVars[0]      = 9;
                g_SceneState.step_05 = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 0x14) {
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                g_AreaDrawFlags       = 0;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_AREA, TO_COORD(54), TO_COORD(80), 0);
                Scene_RequestChapterAdvance();
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801FC488);
#endif
