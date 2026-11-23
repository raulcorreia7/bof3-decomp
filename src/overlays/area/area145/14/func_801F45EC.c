#include "area145_14.h"
#include "menu/save_data.h"

/* Runs the area 145 opening scene: the two actor spawns, the scroll route and the window that
 * closes it. */
MATCH void func_801F45EC(void) {
    u8 slot;
    u8 result;

    switch (g_SceneEventState.step) {
        case 2:
        case 4:
        case 6:
            g_ScriptVars[3]        = g_SceneEventState.step;
            g_SceneEventState.step = 8;
            break;
        case 8:
            if (g_ScriptVars[3] == 0) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 10:
            SYS_SetFlag(g_SaveData.scene_event_flags, 0x2C);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
            Area_ScrollStartRoute(0);
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot == GAME_NONE) {
                break;
            }
            g_SpawnedActors[slot].header.flags                          = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x31A;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x260;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x30;
            g_SceneEventState.step                                      = 11;
            break;
        case 11:
            if (g_ScriptVars[3] != 0x40) {
                break;
            }
            g_SceneEventState.step       = 12;
            g_SaveData.scene_event_timer = 0;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
            break;
        case 12:
            result = func_801F4CF0(++g_SaveData.scene_event_timer);
            switch (result) {
                case 1:
                    break;
                case 0:
                    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x2D) == 0) {
                        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
                        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 7));
                        g_SceneEventState.step = 0x1E;
                        break;
                    }
                default:
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
                    g_SceneEventState.step = 0x14;
                    break;
            }
            break;
        case 20:
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot == GAME_NONE) {
                break;
            }
            g_SpawnedActors[slot].header.flags                          = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x30;
            g_AreaScrollTargetX                                         = g_Game.members[0].pos.x.fixed;
            g_AreaScrollTargetY                                         = g_Game.members[0].pos.y.fixed;
            g_SceneEventState.step                                      = 0x15;
            break;
        case 21:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[3]        = 0;
            g_SceneEventState.step = 0x16;
            break;
        case 22:
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x2C);
            Game_ClearScriptActive();
            g_SceneEventState.mode = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            break;
        case 25:
            g_Game.members[0].header.mode = 2;
            g_Game.members[0].header.step = 3;
            g_SaveData.scene_event_timer  = 0x17;
            g_Game.members[0].unk_03      = 0;
            g_SceneEventState.step        = 0x1A;
            break;
        case 26:
            if (g_SaveData.scene_event_timer == 0) {
                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_COLONY_OUTSIDE, TO_COORD_HALF(59), TO_COORD(93), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x2E) == 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 12));
                    SYS_SetFlag(g_SaveData.scene_event_flags, 0x2E);
                }
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            } else {
                g_SaveData.scene_event_timer--;
            }
            break;
        case 30:
            UI_ModeSet(8);
            g_AreaScrollTargetX    = TO_COORD_HALF(48);
            g_AreaScrollTargetY    = TO_COORD_HALF(99);
            g_SceneEventState.step = 0x1F;
            break;
        case 31:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            UI_ModeSet(9);
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x3E;
            }
            g_SceneEventState.step = 0x20;
            break;
        case 32:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_SaveData.scene_event_timer = 0x1E;
            g_SceneEventState.step       = 0x21;
            break;
        case 33:
            if (g_SaveData.scene_event_timer == 0) {
                g_SceneEventState.step = 0x22;
            } else {
                g_SaveData.scene_event_timer--;
            }
            break;
        case 34:
            SYS_SetFlag(g_SaveData.scene_event_flags, 0x2D);
            Game_RequestAreaChange(AREA_ID_COLONY_OUTSIDE, TO_COORD(10), TO_COORD(99), AREA_ENTRY_MAP_LOADING | FACING_UP_LEFT);
            g_SceneEventState.step = 0x23;
            break;
        case 35:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_SaveData.scene_event_timer = 0x5A;
            g_SceneEventState.step       = 0x24;
            break;
        case 36:
            if (g_SaveData.scene_event_timer == 0) {
                Game_RequestAreaChange(AREA_ID_COLONY_OUTSIDE, TO_COORD(62), TO_COORD(95), FACING_UP);
                g_SceneEventState.step = 0x16;
            } else {
                g_SaveData.scene_event_timer--;
            }
            break;
    }
}
