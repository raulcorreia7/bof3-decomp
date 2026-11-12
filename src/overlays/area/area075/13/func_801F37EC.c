#include "area075_13.h"
#include "audio/audio.h"
#include "menu/save_data.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F37EC(void) {
    u32 step;
    s32 delta;

    switch (g_SceneEventStep) {
        case 0:
            UI_SetMode(0);
            g_SceneEventStep = 1;
            break;

        case 1:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags  = 0;
                g_SceneEventStep = 2;
            }
            break;

        case 2:
            SYS_SetFlag(g_SaveData.scene_event_flags, 0x41);
            Game_RequestAreaChange(75, TO_COORD(23), TO_COORD(25), 130);
            g_GamePrevSelection = 0x58;
            if (SYS_TestFlag(&D_80144ED8, 1)) {
                g_ScriptVars[0] = 0x13;
            } else {
                g_ScriptVars[0] = 0;
            }
            g_SceneEventStep = 3;
            break;

        case 3:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(1);
                g_SceneEventStep = 4;
            }
            break;

        case 4:
            if (WINDOW_EFFECT_IDLE()) {
                g_ScriptVars[0]  = 1;
                g_SceneEventStep = 5;
            }
            break;

        case 5:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            func_801F4034();
            D_801F58C0 = 2;
            D_801F58C3 = 0;
            D_801F58C9 = 0;
            D_801F58C6 |= 8;
            TASK_SET(&g_Actors[D_801F58D0]);
            Actor_RequestScript(2);
            g_Task->unk_2A   = 1;
            g_SceneEventStep = 6;
            break;

        case 6:
            if (D_801F58CC < 0x579) {
                D_801F58C0       = 0;
                g_SceneEventStep = 7;
                g_ScriptVars[0]++;
            }
            break;

        case 7:
            if (g_ScriptVars[0] == 6) {
                D_801F58C0       = 2;
                D_801F58C3       = 1;
                g_SceneEventStep = 8;
            }
            break;

        case 8:
            if (D_801F58CA < 0x579) {
                D_801F58C0       = 0;
                g_SceneEventStep = 9;
                g_ScriptVars[0]++;
            }
            break;

        case 9:
            if (g_ScriptVars[0] == 9) {
                Message_StartAreaMessage(23);
                g_GameStateIndex = 2;
                g_SceneEventStep = 10;
                D_801F58C6 |= 4;
            }
            break;

        case 10:
            if (g_GameStateIndex != 2) {
                D_801F58C0 = 2;
                D_801F58C3 = 0;
                D_801F58C9 = 0;
                TASK_SET(&g_Actors[D_801F58D0]);
                Actor_RequestScript(2);
                g_Task->unk_2A   = 1;
                g_SceneEventStep = 11;
            }
            break;

        case 11:
            delta = D_801F58CA - D_801F58CC;
            if (delta < 0) {
                delta = -delta;
            }
            if (delta >= 0x97) {
                g_SceneEventStep = 12;
                g_ScriptVars[0]++;
            }
            break;

        case 12:
            if (D_801F58CC < 0x47F) {
                D_801F58C0       = 0;
                g_SceneEventStep = 13;
                g_ScriptVars[0]++;
            }
            break;

        case 13:
            if (g_ScriptVars[0] == 12) {
                func_801F4034();
                g_SceneEventStep = 14;
            }
            break;

        case 15:
            if (--g_SaveData.scene_event_timer == 0) {
                g_SceneEventStep = 4;
            }
            break;

        case 20:
            if (g_GameStateIndex != 2) {
                func_801F4034();
                D_801F58C0 = 2;
                D_801F58C3 = 0;
                D_801F58C4 = 0x78;
                TASK_SET(&g_Actors[D_801F58D0]);
                Actor_RequestScript(2);
                g_Task->unk_2A = 1;
                TASK_SET(&g_Actors[D_801F58D1]);
                Actor_RequestScript(2);
                g_Task->unk_2A = 0;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
                g_SceneEventStep = 21;
            }
            break;

        case 21:
            func_801F4080();
            break;

        case 30:
            g_Actors[D_801F58D0].unk_7E++;
            *(u16*)&g_Game.members[0].u.turn.choice += 1;
            g_SceneEventStep = 31;
            break;

        case 31:
            if (g_ScriptVars[0] == 0x1A) {
                UI_SetMode(0);
                SND_StartDecrescendo(g_SelectionCues[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 100, 32);
                g_SceneEventStep = 32;
            }
            break;

        case 32:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0;
                SND_StopSequence(g_SelectionCues[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4]);
                SND_StartXAStream(6, 1);
                Message_StartAreaMessage(27);
                g_GameStateIndex = 2;
                g_SceneEventStep = 33;
            }
            break;

        case 33:
            if (g_GameStateIndex != 2 && SND_IsXAIdle() != 0) {
                g_SceneEventStep = 34;
            }
            break;

        case 34:
            SYS_ClearFlag(g_SaveData.scene_event_flags, 0x41);
            Game_RequestAreaChange(75, 0x198000, 0x1B8000, 0x83);
            g_SceneEventStep = 35;
            break;

        case 35:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(1);
                g_ScriptVars[0] = 1;
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
    }

    step = g_SceneEventStep;
    if (step - 6 < 9) {
        func_801F4080();
    }
}
#else
INCLUDE_ASM(func_801F37EC);
#endif
