#include "area135_14.h"

MATCH void func_801F529C(void) {
    u8*  game_state;
    u8*  selection;
    u8   xa_idle;
    u8   at_cell;
    u8   flag_bits;
    u16  countdown;
    u16* timer;

    switch (g_SceneEventState.step) {
        case 0:
            game_state = &g_GameStateIndex;
            if (*game_state != GAME_REQUEST_MESSAGE) {
                Item_VitalAdd(VITAL_ITEM_ID_CARD);
                UI_MessageStartArea(MSG_AREA135_FOUND_ID_CARD);
                *game_state = GAME_REQUEST_MESSAGE;
                SND_BGMPause(g_SndBGMId);
                SND_XAStartStream(2, 1);
                g_SceneEventState.step = 1;
            }
            break;
        case 1:
            xa_idle = SND_XAIsIdle();
            if (xa_idle != 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_BGMResume(g_SndBGMId);
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 5:
            at_cell = func_801F60E0();
            if (at_cell != 0) {
                UI_MessageStartArea(MSG_AREA135_CATWALK_WARNING);
                goto message_request;
            } else {
                SYS_ToggleFlag(g_SceneEventFlags, 42);
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
                D_801448EE             = 10;
                g_SceneEventState.step = 6;
            }
            break;
        case 6:
            timer     = &D_801448EE;
            countdown = *timer;
            if (countdown == 0) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            } else {
                *timer = countdown - 1;
            }
            break;
        case 10:
            if (SYS_TestFlag(g_SceneEventFlags, 12)) {
                sprintf(g_TextVariables, D_801F2C04, g_SceneEventState.selection);
                UI_MessageStartArea(MSG_AREA135_PLATFORM_ACTIVATED);
            } else {
                UI_MessageStartArea(MSG_AREA135_PLATFORM_PROGRAM_NOTICE);
                SYS_SetFlag(g_SceneEventFlags, 12);
            }
        message_request:
            g_GameStateIndex       = GAME_REQUEST_MESSAGE;
            g_SceneEventState.step = 11;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801F6168(g_RouteSpeedScale[3] << 3);
                g_AreaCameraHeightDelta = 0;
                g_SceneEventState.step  = 21;
            }
            break;
        case 21:
            if (g_AreaCameraMoving == 0) {
                func_801F61A8(139);
                g_SpawnedActors[g_SceneActorSlot].header.mode = 2;
                g_SceneEventState.step                        = 22;
                g_AreaCameraSpeed                             = g_RouteSpeedScale[3] << 3;
            }
            break;
        case 22:
            if (g_PadStates[0].held & PADRdown) {
                func_801F61A8(140);
                g_SpawnedActors[g_SceneActorSlot].header.mode = 3;
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
                g_ScriptVars[3]        = 10;
                g_SceneEventState.step = 23;
            }
            break;
        case 23:
            func_801F6168(0);
            if (g_ScriptVars[3] == 11) {
                func_801F61A8(141);
                g_SpawnedActors[g_SceneActorSlot].header.mode = 2;
                g_SceneEventState.step                        = 24;
            }
            break;
        case 24:
            if (g_PadStates[0].pressed & PADRdown) {
                g_SceneEventState.step = 25;
            }
            break;
        case 25:
            if (g_PadStates[0].held & PADRdown) {
                func_801F61A8(142);
                g_SpawnedActors[g_SceneActorSlot].header.mode = 3;
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
                g_ScriptVars[3]        = 12;
                g_SceneEventState.step = 26;
            }
            break;
        case 26:
            func_801F6168(0);
            if (g_ScriptVars[3] == 13) {
                g_SpawnedActors[g_SceneActorSlot].header.mode = 4;
                g_SceneEventState.step                        = 27;
            }
            break;
        case 27:
            func_801F6168(0);
            if (g_ScriptVars[3] == 16) {
                selection = &g_SceneEventState.selection;
                if (*selection != GAME_NONE) {
                    /* FAKE: each actor write reloads the selection byte; plain C measures 474 of 490 instructions. */
                    g_Actors[*selection].header.mode = 7;
                    g_Actors[*selection].unk_18      = 0;
                    FAKE_BARRIER();
                    g_Actors[*selection].unk_1C = 5;
                    FAKE_BARRIER();
                    g_Actors[*selection].unk_7E += 3;
                    g_SceneEventState.step = 28;
                } else {
                    func_801F61A8(143);
                    g_SceneEventState.step = 30;
                }
            }
            break;
        case 28:
            if (g_ScriptVars[3] == 17) {
                u8* flags              = &D_801F69AF;
                flag_bits              = *flags;
                g_SceneEventState.step = 29;
                *flags                 = flag_bits | 0x10;
            }
            break;
        case 29:
            func_801F6168(0);
            if (g_ScriptVars[3] == 18) {
                u8* flags                        = &D_801F69AF;
                selection                        = &g_SceneEventState.selection;
                g_Actors[*selection].header.mode = 4;
                g_Actors[*selection].active_flags &= ~0x20;
                g_Actors[*selection].unk_7E += 1;
                *flags &= ~0x10;
                func_801F61A8(143);
                g_SceneEventState.step = 30;
            }
            break;
        case 30:
            func_801F6168(0);
            if (g_ScriptVars[3] == 21) {
                g_AreaScrollTargetX                           = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY                           = g_Game.members[0].pos.y.fixed;
                g_AreaCameraSpeed                             = g_RouteSpeedScale[3] << 3;
                g_SpawnedActors[g_SceneActorSlot].header.mode = 5;
                g_SceneEventState.step                        = 31;
            }
            break;
        case 31:
            if (g_AreaCameraMoving == 0) {
                Game_ClearScriptActive();
                g_ScriptVars[3]             = 0;
                g_SceneEventState.mode      = SCENE_EVENT_NONE;
                g_SceneEventState.step      = 0;
                g_SceneEventState.selection = 0;
            }
            break;
    }
}
