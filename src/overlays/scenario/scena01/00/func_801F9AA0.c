#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Runs the scene script one step per frame, keyed on g_ScenarioState.step. */
MATCH void func_801F9AA0(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_UiMessageRequest == 2 && (g_UiWindowChannel & 2) && SYS_TestFlag(D_80145004, 4)) {
                Game_SetScriptActive();
                g_ScriptVars[0]          = 5;
                g_ScenarioState.step     = 1;
                g_ScenarioState.state_04 = 6;
            }
            break;
        case 1:
            SYS_SetFlag(g_SceneFlags, 6);
            g_ScenarioState.step = 2;
            func_801BE1B0(2);
            g_ScriptVars[3] = 0;
            break;
        case 2:
            if (g_ScriptVars[0] == 0xC) {
                SND_SeqStop(0, 1);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x23) {
                SCENARIO_RETURN_TO_START();
                g_ScriptVars[1] = 3;
                g_ScriptVars[2] = 3;
                g_ScriptVars[0] = 0;
                Game_ClearScriptActive();
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 2) {
                SND_BGMPlay(10, 100, 8);
                g_AreaDrawFlags = 0;
                func_801C601C(1);
                g_ScenarioState.step = 0xB;
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 3) {
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x1A) {
                g_ScenarioState.step = 0xF;
                UI_ModeSet(4);
            }
            break;
        case 15:
            if (g_SysThreads[2].state == 0) {
                g_ScenarioState.step = 0x10;
                g_ScriptVars[2]      = 4;
                g_AreaDrawFlags      = 0;
                g_Characters[g_CharSlot[CHAR_ID_REI]].party_flags &= ~PARTY_FLAG_JOINED;
                func_801C1E3C(0);
                SYS_SetFlag(g_SceneFlags, 5);
                Game_RequestAreaChange(8, TO_COORD(0x32), TO_COORD(0x12), 0x84);
            }
            break;
        case 16:
            if (g_GameStateIndex != 2 && g_ScriptVars[0] == 1) {
                g_ScriptVars[0]      = 2;
                g_ScenarioState.step = 0x11;
            }
            break;
        case 17:
            if (g_ScriptVars[0] == 5) {
                SND_BGMPlay(9, 100, 8);
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x15;
                }
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x55;
                }
                g_ScenarioState.step = 0x12;
            }
            break;
        case 18:
            if (g_ScriptVars[3] & 0x80) {
                g_GameState = &g_Game.members[0];
                SELF_SET(&g_Game.members[0]);
                g_ScenarioState.step = 0x14;
                D_80145FA8 &= 0xBF;
            } else if (g_ScriptVars[1] != 2 && g_PadStates[0].pressed == 0x10) {
                g_GameState = &g_Game.members[0];
                SELF_SET(&g_Game.members[0]);
                D_80145FA8 |= 0x40;
                SND_SEPlay(0x20F);
                Script_Select(0x44);
                g_ScriptVars[1]      = 1;
                g_ScenarioState.step = 0x13;
            }
            break;
        case 19:
            g_GameState = &g_Game.members[0];
            SELF_SET(&g_Game.members[0]);
            if (g_Game.members[0].unk_58 == 0xC && g_Game.members[0].unk_4A == 1) {
                Script_Select(5);
                g_ScenarioState.step = 0x12;
            }
            break;
        case 20:
            if (g_ScriptVars[2] & 0x80) {
                g_ScriptVars[0]      = 6;
                g_ScenarioState.step = 0x19;
            } else {
                g_ScriptVars[0]      = 7;
                g_ScenarioState.step = 0x15;
            }
            break;
        case 21:
            if (g_ScriptVars[0] == 0x1E) {
                g_ScriptVars[0]          = 0x1F;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.timer_06 = 0;
                SND_BGMPlay(9, 100, 8);
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x15;
                }
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x55;
                }
                g_GameState = &g_Game.members[0];
                SELF_SET(&g_Game.members[0]);
                g_GameState = &g_Game.members[1];
                SELF_SET(&g_Game.members[1]);
                D_80145FA8 |= 0x40;
                D_801460E8 |= 0x40;
                func_801BE1B0(5);
                g_ScenarioState.step = 0x12;
            }
            break;
        case 25:
            func_801BE1B0(6);
            func_801C601C(2);
            g_ScenarioState.step = 0x1A;
            break;
        case 26:
            if (g_ScriptVars[0] == 0xF && !g_AreaCameraMoving) {
                D_80146258 ^= 0x10;
                SYS_SetFlag(g_SceneFlags, 7);
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.timer_06 = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
