#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Step script: the cutscene actors, timers and music cues that end with scene flag 8. */
MATCH void func_801F8C00(void) {
    switch (g_ScenarioState.step) {
        case 0:
            func_801BE1B0(0);
            EMI_ArchiveLoad(0x290);
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 1;
            break;
        case 1:
            if (--g_ScenarioState.timer_06 == 0) {
                UI_MessageStartArea((s16)func_801FD31C());
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 4 && EMI_IsReady()) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x68;
                    actor->header.mode  = 0;
                    actor->pos.x.fixed  = TO_COORD_HALF(5);
                    actor->pos.y.fixed  = TO_COORD_HALF(5);
                    actor->pos.z.fixed  = TO_COORD(0x200);
                }
                g_ScenarioState.timer_06 = 0x5A;
                g_ScenarioState.step     = 4;
            }
            break;
        case 4:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 5;
                g_ScriptVars[0]++;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 8) {
                func_8019FA28(0x62, TO_COORD(56), TO_COORD(36), 1);
                g_GamePrevSelection      = 0xFF;
                g_ScenarioState.timer_06 = 0x55;
                g_ScenarioState.step     = 6;
            }
            break;
        case 6:
            if (g_UiWindowEffectBusy == 0) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x61;
                    actor->unk_06       = 0;
                    actor->unk_07       = 0;
                }
                g_ScenarioState.timer_06 = 0x55;
                g_ScenarioState.step     = 7;
            }
            break;
        case 7:
            if (--g_ScenarioState.timer_06 == 0) {
                SND_BGMPlay(0x7B, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0xA) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x61;
                    actor->unk_06       = 0;
                    actor->unk_07       = 1;
                }
                g_ScenarioState.timer_06 = 0x55;
                g_ScenarioState.step     = 9;
            }
            break;
        case 9:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScriptVars[0]      = 0xB;
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 0x10) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x62;
                    actor->pos.x.fixed  = TO_COORD(56);
                    actor->pos.y.fixed  = TO_COORD(38);
                    actor->pos.z.fixed  = TO_COORD(0x280);
                }
                g_ScenarioState.timer_06 = 0xC8;
                g_ScenarioState.step     = 11;
                SND_StartDecrescendo(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 0x64, 0xC8);
            }
            break;
        case 11:
            if (--g_ScenarioState.timer_06 == 0) {
                SND_BGMFadeOut(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, 1);
                g_ScenarioState.step = 12;
                g_ScriptVars[0]++;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x13) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x69;
                    actor->pos.x.fixed  = g_Game.members[0].pos.x.fixed;
                    actor->pos.y.fixed  = g_Game.members[0].pos.y.fixed;
                    actor->pos.z.fixed  = Area_HeightSample(actor->pos.x.fixed, actor->pos.y.fixed) << 16;
                }
                g_ScenarioState.timer_06 = 0x1E;
                g_ScenarioState.step     = 13;
            }
            break;
        case 13:
            if (--g_ScenarioState.timer_06 == 0) {
                UI_ModeSet(8);
                g_ScenarioState.step = 14;
            }
            break;
        case 14:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.timer_06 = 0x3C;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step     = 15;
            }
            break;
        case 15:
            if (--g_ScenarioState.timer_06 == 0) {
                UI_ModeSet(0);
                g_ScenarioState.step = 16;
            }
            break;
        case 16:
            if (g_UiWindowEffectBusy == 0) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA10_019, 17);
            }
            break;
        case 17:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_ScenarioState.step = 18;
            }
            break;
        case 18:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.step = 19;
                g_ScriptVars[0]++;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x16) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x64;
                    actor->pos.x.fixed = actor->camera_angle.x = g_Game.members[0].pos.x.fixed;
                    actor->pos.y.fixed = actor->camera_angle.y = g_Game.members[0].pos.y.fixed;
                    actor->pos.z.fixed = actor->camera_angle.z = (Area_HeightSample(actor->pos.x.fixed, actor->pos.y.fixed) << 16) + TO_COORD(0x80);
                }
                g_ScenarioState.step = 20;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 0x20) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x61;
                    actor->unk_06       = 1;
                    actor->unk_07       = 0;
                }
                g_ScenarioState.timer_06 = 0x1E;
                g_ScenarioState.step     = 21;
            }
            break;
        case 21:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 22;
                g_ScriptVars[0]++;
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 0x22) {
                u8 slot;

                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];

                    actor->header.flags = 1;
                    actor->type         = 0x61;
                    actor->unk_06       = 1;
                    actor->unk_07       = 1;
                }
                g_ScenarioState.timer_06 = 0x1E;
                g_ScenarioState.step     = 23;
            }
            break;
        case 23:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 24;
                g_ScriptVars[0]++;
            }
            break;
        case 24:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_ScriptVars[0] == 0x25) {
                func_8019FA28(0x62, TO_COORD_HALF(6), TO_COORD(7), 0x82);
                g_ScenarioState.step = 25;
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 8) {
                SYS_SetFlag(g_SceneFlags, 8);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
