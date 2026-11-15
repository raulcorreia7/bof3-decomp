#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F529C(void) {
    u8*  game_state;
    u8*  selection;
    u8*  flags;
    u8   xa_idle;
    u8   at_cell;
    u8   flag_bits;
    u16  countdown;
    u16* timer;

    switch (g_SceneEventStep) {
        case 0:
            game_state = &g_GameStateIndex;
            if (*game_state != GAME_REQUEST_MESSAGE) {
                Item_VitalAdd(6);
                Message_StartAreaMessage(129);
                *game_state = GAME_REQUEST_MESSAGE;
                SND_PauseBGM(g_SndBGMId);
                SND_StartXAStream(2, 1);
                g_SceneEventStep = 1;
            }
            break;
        case 1:
            xa_idle = SND_IsXAIdle();
            if (xa_idle != 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_ResumeBGM(g_SndBGMId);
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 5:
            at_cell = func_801F60E0();
            if (at_cell != 0) {
                Message_StartAreaMessage(135);
                goto message_request;
            } else {
                SYS_ToggleFlag(g_SceneEventFlags, 42);
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
                D_801448EE       = 10;
                g_SceneEventStep = 6;
            }
            break;
        case 6:
            timer     = &D_801448EE;
            countdown = *timer;
            if (countdown == 0) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            } else {
                *timer = countdown - 1;
            }
            break;
        case 10:
            if (SYS_TestFlag(g_SceneEventFlags, 12)) {
                sprintf(g_TextVariables, D_801F2C04, g_SceneEventSelection);
                Message_StartAreaMessage(132);
            } else {
                Message_StartAreaMessage(131);
                SYS_SetFlag(g_SceneEventFlags, 12);
            }
        message_request:
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 11;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801F6168(g_RouteSpeedScale[3] << 3);
                g_AreaCameraHeightStep = 0;
                g_SceneEventStep       = 21;
            }
            break;
        case 21:
            if (g_AreaCameraMoving == 0) {
                func_801F61A8(139);
                g_SpawnedActors[D_801F6BC0].header.mode = 2;
                g_SceneEventStep                        = 22;
                g_AreaCameraStep                        = g_RouteSpeedScale[3] << 3;
            }
            break;
        case 22:
            if (g_InputHeld & PADRdown) {
                func_801F61A8(140);
                g_SpawnedActors[D_801F6BC0].header.mode = 3;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 9));
                g_ScriptVars[3]  = 10;
                g_SceneEventStep = 23;
            }
            break;
        case 23:
            func_801F6168(0);
            if (g_ScriptVars[3] == 11) {
                func_801F61A8(141);
                g_SpawnedActors[D_801F6BC0].header.mode = 2;
                g_SceneEventStep                        = 24;
            }
            break;
        case 24:
            if (g_InputPressed & PADRdown) {
                g_SceneEventStep = 25;
            }
            break;
        case 25:
            if (g_InputHeld & PADRdown) {
                func_801F61A8(142);
                g_SpawnedActors[D_801F6BC0].header.mode = 3;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 9));
                g_ScriptVars[3]  = 12;
                g_SceneEventStep = 26;
            }
            break;
        case 26:
            func_801F6168(0);
            if (g_ScriptVars[3] == 13) {
                g_SpawnedActors[D_801F6BC0].header.mode = 4;
                g_SceneEventStep                        = 27;
            }
            break;
        case 27:
            func_801F6168(0);
            if (g_ScriptVars[3] == 16) {
                selection = &g_SceneEventSelection;
                if (*selection != GAME_NONE) {
                    g_Actors[*selection].header.mode = 7;
                    g_Actors[*selection].unk_18      = 0;
                    g_Actors[*selection].unk_1C      = 5;
                    g_Actors[*selection].active_flags &= ~0x20;
                    g_Actors[*selection].unk_7E += 3;
                    g_SceneEventStep = 28;
                } else {
                    func_801F61A8(143);
                    g_SceneEventStep = 30;
                }
            }
            break;
        case 28:
            if (g_ScriptVars[3] == 17) {
                flags            = &D_801F69AF;
                flag_bits        = *flags;
                g_SceneEventStep = 29;
                *flags           = flag_bits | 0x10;
            }
            break;
        case 29:
            func_801F6168(0);
            if (g_ScriptVars[3] == 18) {
                selection                        = &g_SceneEventSelection;
                g_Actors[*selection].header.mode = 4;
                g_Actors[*selection].active_flags &= ~0x20;
                g_Actors[*selection].unk_7E += 1;
                flags = &D_801F69AF;
                *flags &= ~0x10;
                func_801F61A8(143);
                g_SceneEventStep = 30;
            }
            break;
        case 30:
            func_801F6168(0);
            if (g_ScriptVars[3] == 21) {
                g_AreaScrollTargetX                     = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY                     = g_Game.members[0].pos.y.fixed;
                g_AreaCameraStep                        = g_RouteSpeedScale[3] << 3;
                g_SpawnedActors[D_801F6BC0].header.mode = 5;
                g_SceneEventStep                        = 31;
            }
            break;
        case 31:
            if (g_AreaCameraMoving == 0) {
                Game_ClearScriptActive();
                g_ScriptVars[3]       = 0;
                g_SceneEventMode      = SCENE_EVENT_NONE;
                g_SceneEventStep      = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F529C);
#endif
