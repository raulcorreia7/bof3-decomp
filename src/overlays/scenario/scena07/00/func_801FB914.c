#include "scena07_00.h"

#include "area/map.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB914(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            slot                           = Actor_FindFreeSpawned();
            g_Game.members[0].param.unk_0B = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                        = 1;
                g_SpawnedActors[g_Game.members[0].param.unk_0B].type      = 6;
                g_SpawnedActors[g_Game.members[0].param.unk_0B].unk_06    = 1;
                g_SpawnedActors[g_Game.members[0].param.unk_0B].vx        = 0;
                g_SpawnedActors[g_Game.members[0].param.unk_0B].selection = D_80181B28[g_Game.members[0].chr.character_id];
                g_SpawnedActors[g_Game.members[0].param.unk_0B].screen_x  = g_Game.members[0].screen_x.value;
                g_SpawnedActors[g_Game.members[0].param.unk_0B].screen_y  = g_Game.members[0].screen_y.value;
                g_ScenarioState.step                                      = 1;
            }
            break;
        case 1:
            if (g_SpawnedActors[g_Game.members[0].param.unk_0B].header.flags & 1) {
                break;
            }
            g_ScriptVars[0] = 1;
            Area_ScrollStartRoute(0);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            func_801BFE34(TO_COORD(74), TO_COORD(34), 0x1E);
            Scene_SetupParty(0);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SND_BGMFadeOut(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                       = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type        = 0x3B;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].pos.x.fixed = g_Actors[0].pos.x.fixed;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].pos.y.fixed = g_Actors[0].pos.y.fixed;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].pos.z.fixed = g_Actors[0].pos.z.fixed + TO_COORD(256);
                g_ScenarioState.timer_06                                 = 0x8C;
                g_ScenarioState.step                                     = 5;
            }
            break;
        case 5:
            if (g_ScenarioState.timer_06 == 0) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x33E;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0xA0;
                    g_ScriptVars[0]++;
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
                    g_ScenarioState.step = 6;
                }
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0xC) {
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            g_ScenarioState.timer_06 = 0;
            g_ScenarioState.step     = 8;
            break;
        case 8:
            if (g_ScriptVars[0] == 0xE) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x90;
                    g_ScenarioState.step                                        = 9;
                }
            }
            func_801FC094();
            g_ScenarioState.timer_06++;
            break;
        case 9:
            if (g_ScriptVars[0] == 0xF) {
                SND_BGMPlay(0x5E, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                g_ScenarioState.timer_06 = 0;
                g_ScenarioState.step     = 10;
                break;
            }
            func_801FC094();
            g_ScenarioState.timer_06++;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x12) {
                break;
            }
            Game_BattleStartScripted(0x1E);
            g_ScenarioState.step = 11;
            break;
        case 12:
            SYS_SetFlag(g_SceneFlags, 3);
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}
