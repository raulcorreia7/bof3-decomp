#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA6BC(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] == 0x1F) {
                SND_StartDecrescendo(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence, 0x64, 0x20);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            g_AreaCameraOffsetZ -= 5;
            if (g_AreaCameraOffsetZ == -0x280) {
                SND_SeqStop(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence);
                g_AreaDrawMode           = GFX_LAYER_BATTLE_SCENE;
                D_8014933F               = 0;
                g_AreaCameraRefreshCount = 2;
                g_ScenarioState.step     = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x20) {
                func_801BFE34(0x220000, 0x1A8000, 0x24);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x21) {
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            g_AreaCameraOffsetZ += 10;
            if (g_AreaCameraOffsetZ == 0) {
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x23) {
                UI_MessageStartArea((s16)func_801FD278());
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x24) {
                SND_SEPlay(0x207);
                Game_BattleStartScripted(0x24);
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            break;
        case 8:
            SYS_SetFlag(g_SceneFlags, 2);
            Game_RequestAreaChange(0x4B, 0x198000, 0x188000, 0x86);
            g_ScriptVars[0]      = 0x28;
            g_ScenarioState.step = 9;
            break;
        case 9:
            if (g_SysThreads[2].state == 0) {
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
