#include "area145_14.h"

#ifdef NON_MATCHING
/* Runs the area 145 opening scene: the two actor spawns, the scroll route and the window that
 * closes it. */
NON_MATCHING void func_801F45EC(void) {
    u8 slot;
    u8 result;

    switch (g_SceneEventStep) {
        case 2:
        case 4:
        case 6:
            g_ScriptVars[3]  = g_SceneEventStep;
            g_SceneEventStep = 8;
            break;
        case 8:
            if (g_ScriptVars[3] == 0) {
                Game_ClearScriptActive();
                goto cleanup;
            }
            break;
        case 10:
            SYS_SetFlag(g_SceneEventFlags, 0x2C);
            SND_SEPlay(0x200);
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
            g_SceneEventStep                                            = 11;
            break;
        case 11:
            if (g_ScriptVars[3] != 0x40) {
                break;
            }
            g_SceneEventStep = 12;
            D_801448EE       = 0;
            SND_SEPlay(0x204);
            break;
        case 12:
            result = func_801F4CF0(++D_801448EE);
            if (result == 0) {
                if (SYS_TestFlag(g_SceneEventFlags, 0x2D) == 0) {
                    SND_SEPlay(0x205);
                    SND_SEPlay(0x207);
                    g_SceneEventStep = 0x1E;
                } else {
                    SND_SEPlay(0x205);
                    g_SceneEventStep = 0x14;
                }
            } else if (result != 1) {
                SND_SEPlay(0x205);
                g_SceneEventStep = 0x14;
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
            g_SceneEventStep                                            = 0x15;
            break;
        case 21:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[3]  = 0;
            g_SceneEventStep = 0x16;
            break;
        case 22:
            SYS_ClearFlag(g_SceneEventFlags, 0x2C);
            Game_ClearScriptActive();
            goto cleanup;
        case 25:
            g_Game.members[0].header.mode = 2;
            g_Game.members[0].header.step = 3;
            D_801448EE                    = 0x17;
            g_Game.members[0].unk_03      = 0;
            g_SceneEventStep              = 0x1A;
            break;
        case 26:
            if (D_801448EE != 0) {
                D_801448EE--;
                break;
            }
            Game_ClearScriptActive();
            Game_RequestAreaChange(0x91, 0x3B8000, 0x5D0000, 0x82);
            if (SYS_TestFlag(g_SceneEventFlags, 0x2E) == 0) {
                SND_SEPlay(0x20C);
                SYS_SetFlag(g_SceneEventFlags, 0x2E);
            }
            goto cleanup;
        case 30:
            UI_ModeSet(8);
            g_AreaScrollTargetX = 0x308000;
            g_AreaScrollTargetY = 0x638000;
            g_SceneEventStep    = 0x1F;
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
            g_SceneEventStep = 0x20;
            break;
        case 32:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            D_801448EE       = 0x1E;
            g_SceneEventStep = 0x21;
            break;
        case 33:
            if (D_801448EE != 0) {
                D_801448EE--;
                break;
            }
            g_SceneEventStep = 0x22;
            break;
        case 34:
            SYS_SetFlag(g_SceneEventFlags, 0x2D);
            Game_RequestAreaChange(0x91, 0xA0000, 0x630000, 0x80);
            g_SceneEventStep = 0x23;
            break;
        case 35:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            D_801448EE       = 0x5A;
            g_SceneEventStep = 0x24;
            break;
        case 36:
            if (D_801448EE != 0) {
                D_801448EE--;
                break;
            }
            Game_RequestAreaChange(0x91, 0x3E0000, 0x5F0000, 1);
            g_SceneEventStep = 0x16;
            break;
    }
    return;

cleanup:
    g_SceneEventMode = SCENE_EVENT_NONE;
    g_SceneEventStep = 0;
}
#else
INCLUDE_ASM(func_801F45EC);
#endif
