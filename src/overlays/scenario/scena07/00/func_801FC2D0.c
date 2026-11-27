#include "scena07_00.h"
#include "area/map.h"
#include "engine/area/collision/collision.h"
#include "engine/sound/sound.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Advances the scene through its messages and actor effects. */
MATCH void func_801FC2D0(void) {
    SpawnedActor* func_801FD610(u8 mode);
    u8            slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] == 5) {
                func_801C1E3C(0);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 7) {
                SYS_SetFlag(g_SceneFlags, 8);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 5: {
            s32 state = g_GameStateIndex;
            if (state == 2 && g_UIMessageRequest == state) {
                g_ScenarioState.step = 6;
            }
            break;
        }
        case 6:
            if (g_GameStateIndex != 2) {
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            }
            break;
        case 10:
            UI_MessageStartArea(6);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (g_GameStateIndex != 2) {
                func_801C1E3C(1);
                Scene_SetupParty(1);
                g_ScenarioState.step = 12;
            }
            break;
        case 12: {
            SpawnedActor* actor;
            if (g_ScriptVars[0] == 3) {
                actor                    = func_801FD610(0);
                actor->pos.x.fixed       = 0x160000;
                actor->pos.y.fixed       = 0x3E0000;
                g_ScenarioState.timer_06 = 0xC8;
                g_ScenarioState.step     = 13;
            }
            break;
        }
        case 13:
            if (g_ScenarioState.timer_06 == 0x88) {
                func_801FD610(1);
            }
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 14;
                g_ScriptVars[0]++;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 14: {
            SpawnedActor* actor;
            if (g_ScriptVars[0] == 7) {
                actor                    = func_801FD610(0);
                actor->pos.x.fixed       = 0x360000;
                actor->pos.y.fixed       = 0x410000;
                g_ScenarioState.timer_06 = 0xA8;
                g_ScenarioState.step     = 15;
            }
            break;
        }
        case 15: {
            SpawnedActor* landed;
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                landed              = func_801FD610(2);
                landed->vx          = 0x270000;
                landed->pos.x.fixed = 0x390000;
                landed->pos.y.fixed = 0x410000;
                landed->selection   = 0x410000;
                {
                    Coord sample_x = {landed->vx};
                    Coord sample_y = {0x410000};

                    landed->pos.z.fixed = Area_HeightSample(sample_x.fixed, sample_y.fixed) << 16;
                }
                g_ScenarioState.timer_06 = 8;
                g_ScenarioState.step     = 16;
            }
            break;
        }
        case 16:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.timer_06 = 1;
                g_ScenarioState.step     = 17;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 17:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 18;
                g_ScriptVars[0]++;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 18:
            if (g_ScriptVars[0] == 0x13) {
                g_GameFlags |= 0x80;
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x1F);
                func_801C7A54(0x1F);
                g_ScenarioState.step = 19;
            }
            break;
        case 20:
            SYS_SetFlag(g_SceneFlags, 9);
            Game_RequestAreaChange(0x55, 0x258000, 0x410000, 0x82);
            g_GameRequestType    = 5;
            g_GameEntryMode      = 4;
            g_ScenarioState.step = 21;
            break;
        case 21:
            if (g_ScriptVars[0] == 0x14) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x46;
                    g_ScenarioState.step                              = 22;
                }
            }
            break;
        case 22: {
            SpawnedActor* actor;
            if (g_ScriptVars[0] == 0x15) {
                actor              = func_801FD610(9);
                actor->unk_06      = 0;
                actor->pos.x.fixed = 0x170000;
                actor->pos.y.fixed = 0x3F0000;
                actor->pos.z.fixed = TO_COORD(0x5C0);
                actor->vx          = 0x10000;
                actor->unk_14      = -0x200000;
                actor->counter_18  = 0x2D0000;
                actor->selection   = 0;
                actor->counter_1C  = 0x3F0000;
                actor->unk_20      = TO_COORD(0x300);
                SND_SEPlay(0x203);
                SND_SEPlay(0x206);
                g_ScenarioState.timer_06 = 0x78;
                g_ScenarioState.step     = 23;
            }
            break;
        }
        case 23: {
            SpawnedActor* actor;
            if (g_ScenarioState.timer_06 == 0) {
                actor                    = func_801FD610(9);
                actor->unk_06            = 1;
                actor->pos.x.fixed       = 0x2D0000;
                actor->pos.y.fixed       = 0x410000;
                actor->pos.z.fixed       = TO_COORD(0x300);
                actor->vx                = -0x10000;
                actor->selection         = 0;
                actor->unk_14            = 0;
                actor->counter_18        = 0x270000;
                actor->counter_1C        = 0x410000;
                actor->unk_20            = TO_COORD(0x300);
                g_ScenarioState.timer_06 = 10;
                g_ScenarioState.step     = 24;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        }
        case 24:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.timer_06 = 0x5A;
                g_ScenarioState.step     = 25;
                g_ScriptVars[0]++;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 25:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.timer_06 = 0x10;
                g_ScenarioState.step     = 26;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 26:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 27;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 27:
            if (g_ScriptVars[0] == 0x1A) {
                g_AreaDrawFlags = 0;
                SND_BGMPause(g_SndBGMId);
                UI_MessageStartArea(MSG_SCENA07_017);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 28;
            }
            break;
        case 28:
            if (g_GameStateIndex != 2) {
                g_AreaScrollTargetX = 0x258000;
                g_AreaScrollTargetY = 0x410000;
                Area_InitMapRenderer();
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 29;
                g_ScriptVars[0]++;
            }
            break;
        case 29:
            if (g_ScriptVars[0] == 0x1C) {
                g_AreaDrawFlags = 0;
                UI_MessageStartArea(0x12);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 30;
            }
            break;
        case 30:
            if (g_GameStateIndex != 2) {
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 31;
                g_ScriptVars[0]++;
            }
            break;
        case 31:
            if (g_ScriptVars[0] == 0x1E) {
                SND_SEPlay(0x202);
                g_ScenarioState.step = 32;
            }
            break;
        case 32: {
            SpawnedActor* actor;
            if (g_ScriptVars[0] == 0x1F) {
                actor                    = func_801FD610(3);
                actor->pos.x.fixed       = 0x258000;
                actor->pos.y.fixed       = 0x410000;
                actor                    = func_801FD610(4);
                actor->pos.x.fixed       = 0x258000;
                actor->pos.y.fixed       = 0x410000;
                g_ScenarioState.timer_06 = 0x70;
                g_ScenarioState.step     = 33;
            }
            break;
        }
        case 33: {
            SpawnedActor* actor;
            if (g_ScenarioState.timer_06 == 0) {
                actor                    = func_801FD610(5);
                actor->pos.x.fixed       = 0x258000;
                actor->pos.y.fixed       = 0x410000;
                actor                    = func_801FD610(8);
                actor->pos.x.fixed       = 0x258000;
                actor->pos.y.fixed       = 0x410000;
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 34;
                g_ScriptVars[0]++;
                SND_BGMFadeOut(g_SndBGMId, 100, 8);
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        }
        case 34:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step     = 35;
                g_ScenarioState.timer_06 = 0x96;
                g_ScriptVars[0]++;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 35: {
            SpawnedActor* actor;
            if (g_ScenarioState.timer_06 == 0) {
                actor                    = func_801FD610(6);
                actor->pos.x.fixed       = 0x258000;
                actor->pos.y.fixed       = 0x410000;
                actor                    = func_801FD610(7);
                actor->pos.x.fixed       = 0x258000;
                actor->pos.y.fixed       = 0x410000;
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 36;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        }
        case 36:
            if (g_ScriptVars[0] == 0x25) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x370;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0xB6;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0xA8;
                    g_ScenarioState.step                                        = 37;
                }
            }
            break;
        case 37:
            if (g_ScriptVars[0] == 0x26) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x1E;
                    g_ScenarioState.step                                        = 38;
                }
            }
            break;
        case 38:
            if (g_ScriptVars[0] == 0x27) {
                func_801FD000();
                g_ScenarioState.step = 39;
            }
            break;
        case 39:
            if (g_ScriptVars[0] == 0x29) {
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                func_801A78F8();
                Game_RequestAreaChange(0x20, 0x900000, 0x550000, 3);
                g_GameEntryMode = 4;
                SND_SEPlay(0x20A);
                g_GameFlags &= ~0x80;
            }
            break;
    }
    if (g_ScenarioState.step >= 0x20) {
        func_801FCFB4();
    }
    if (g_ScenarioState.step >= 0x27) {
        func_801FCFB4();
    }
}
