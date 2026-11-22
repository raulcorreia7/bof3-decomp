#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The Wyndia rooftop confrontation: the shop hand-off, the party-size choice and the escape route. */
MATCH void func_801FA24C(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_Game.members[0].pos.x.part.integer == 0x1B && g_Game.members[0].pos.y.part.integer < 0x24) {
                Game_SetScriptActive();
                g_ScenarioState.timer_06   = 0;
                g_ScenarioState.step       = 1;
                g_ScriptVars[0]            = 1;
                g_ScriptVars[3]            = 0;
                g_SndVoiceTargetVolume[23] = 0x7F;
                g_SndVoiceVolume[23]       = 0;
                Scene_SetupParty(6);
                func_801C601C(0);
                g_AreaSceneMode = 1;
            }
            if (g_Game.members[0].pos.x.part.integer == 0x1C && g_Game.members[0].pos.y.part.integer < 0x24) {
                Game_SetScriptActive();
                g_ScenarioState.timer_06   = 0;
                g_ScenarioState.step       = 1;
                g_ScriptVars[0]            = 1;
                g_ScriptVars[3]            = 0;
                g_SndVoiceTargetVolume[23] = 0x7F;
                g_SndVoiceVolume[23]       = 0;
                Scene_SetupParty(6);
                func_801C601C(0);
                g_AreaSceneMode = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 3 && Camera_TurnX(-0x5A, -2) == 0) {
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            g_ScenarioState.timer_06++;
            if (g_ScenarioState.timer_06 >= 110) {
                g_ScriptVars[0]          = 5;
                g_ScenarioState.timer_06 = 0;
                g_ScenarioState.step     = 3;
                SND_SEPlay(0x200);
                g_AreaSceneMode = 2;
            }
            break;
        case 3:
            g_ScenarioState.timer_06++;
            if (g_ScenarioState.timer_06 >= 180) {
                SND_SEPlay(0x207);
                g_ScenarioState.timer_06 = 0;
                g_ScriptVars[0]          = 8;
                g_ScenarioState.step     = 4;
            }
            break;
        case 4:
            if (Camera_TurnX(-0x3C, 2) == 0) {
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            g_ScenarioState.timer_06++;
            if (g_ScenarioState.timer_06 >= 110) {
                g_ScenarioState.timer_06 = 0;
                g_ScenarioState.step     = 6;
                g_ScriptVars[0]          = 15;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x12) {
                u8* flags = &g_ScenarioState.flags_01;

                g_ScriptVars[2]      = 3;
                g_ScenarioState.step = 0xE;
                *flags |= 1;
                SYS_SetFlag(g_SceneFlags, 9);
                func_8019FA28(0x17, TO_COORD(0x48), TO_COORD(6), 0x87);
            }
            break;
        case 14:
            if (g_ScriptVars[0] == 0x14) {
                g_ScriptVars[2]      = 4;
                g_ScenarioState.step = 15;
                func_8019FA28(0x17, TO_COORD(0x4B), TO_COORD(5), 0x88);
            }
            break;
        case 15:
            g_ScenarioState.timer_06 = 120;
            SND_SeqStop(0, 0);
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 16;
        case 16: {
            u16 timer;

            timer                    = g_ScenarioState.timer_06;
            g_ScenarioState.timer_06 = timer - 1;
            if (timer == 0) {
                SND_SEPlay(0x204);
                UI_MessageStartArea(MSG_SCENA01_019);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 17;
            }
            break;
        }
        case 17:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_ModeSet(0xE);
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 18;
            }
            break;
        case 18:
            if (g_SysThreads[2].state == 0) {
                g_ScriptVars[0]      = 6;
                g_ScenarioState.step = 19;
                func_801C16B8();
                SND_BGMPlay(0x1D, 0x64, 8);
                g_GameFlags |= 0x80;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0xB) {
                Game_ClearScriptActive();
                g_ScriptVars[2]          = 7;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 8;
            }
            break;
        case 55:
            if (g_ScriptVars[0] == 0x1F) {
                func_801C601C(1);
                g_ScenarioState.step = 56;
            }
            break;
        case 56:
            if (g_ScriptVars[0] == 0x20) {
                func_801BFE34(TO_COORD(30), TO_COORD(26), 2);
                func_801C601C(2);
                g_ScenarioState.step = 57;
            }
            break;
        case 57:
            if (g_ScriptVars[0] == 0x23) {
                g_ScenarioState.step = 58;
                func_801C7A54(2);
            }
            break;
        case 58:
            if (g_ScriptVars[0] == 0x24) {
                g_ScenarioState.step = 59;
                g_GameFlags ^= 0x80;
            }
            break;
        case 59:
            g_ScenarioState.step = 60;
            g_ScriptVars[0]      = 40;
            break;
        case 60:
            if (g_ScriptVars[0] == 40) {
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                SCENARIO_RETURN_TO_START();
                g_ScenarioState.timer_06 = 0;
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 10);
            }
            break;
    }
}
