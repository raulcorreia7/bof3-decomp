#include "area075_13.h"

/* The area's scene event: the cutscene steps that arm the window effect and the
 * music, hand the script request to the two actors and give the field back. */
MATCH void func_801F37EC(void) {
    switch (g_SceneEventStep) {
        case 0:
            UI_ModeSet(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (!g_SysThreads[2].state) {
                g_AreaDrawFlags  = 0;
                g_SceneEventStep = 2;
            }
            break;
        case 2:
            SYS_SetFlag(g_SceneEventFlags, 0x41);
            Game_RequestAreaChange(0x4B, 0x170000, 0x190000, 0x82);
            g_GamePrevSelection = 0x58;
            /* The area's event flag word sits 0x50 bytes before g_SceneEventFlags. */
            if (SYS_TestFlag(g_SceneEventFlags - 0x50, 1) != 0) {
                g_ScriptVars[0] = 0x13;
            } else {
                g_ScriptVars[0] = 0;
            }
            g_SceneEventStep = 3;
            break;
        case 3:
            if (!g_SysThreads[2].state) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_SceneEventStep = 4;
            }
            break;
        case 4:
            if (!g_SysThreads[2].state) {
                g_ScriptVars[0]  = 1;
                g_SceneEventStep = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 3) {
                u8* flags = &D_801F58C6;

                func_801F4034();
                D_801F58C0 = 2;
                D_801F58C3 = 0;
                D_801F58C9 = 0;
                *flags |= 8;
                g_Self = &g_Actors[D_801F58D0];
                Script_Request(2);
                SELF(Actor)->mirror = 1;
                g_SceneEventStep    = 6;
            }
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
                u8* flags = &D_801F58C6;

                UI_MessageStartArea(0x17);
                g_GameStateIndex = 2;
                *flags |= 4;
                g_SceneEventStep = 0xA;
            }
            break;
        case 10:
            if (g_GameStateIndex != 2) {
                D_801F58C0 = 2;
                D_801F58C3 = 0;
                D_801F58C9 = 0;
                g_Self     = &g_Actors[D_801F58D0];
                Script_Request(2);
                SELF(Actor)->mirror = 1;
                g_SceneEventStep    = 0xB;
            }
            break;
        case 11:
            if (abs(D_801F58CA - D_801F58CC) >= 0x97) {
                g_SceneEventStep = 0xC;
                g_ScriptVars[0]++;
            }
            break;
        case 12:
            if (D_801F58CC < 0x47F) {
                D_801F58C0       = 0;
                g_SceneEventStep = 0xD;
                g_ScriptVars[0]++;
            }
            break;
        case 13:
            if (g_ScriptVars[0] == 0xC) {
                func_801F4034();
                g_SceneEventStep = 0xE;
            }
            break;
        case 15: {
            u16* timer = &D_801448EE;

            if (TIMER_EXPIRED(*timer)) {
                g_SceneEventStep = 4;
            }
        } break;
        case 20:
            if (g_GameStateIndex != 2) {
                func_801F4034();
                D_801F58C0 = 2;
                D_801F58C3 = 0;
                D_801F58C4 = 0x78;
                g_Self     = &g_Actors[D_801F58D0];
                Script_Request(2);
                SELF(Actor)->mirror = 1;
                g_Self              = &g_Actors[D_801F58D1];
                Script_Request(2);
                SELF(Actor)->mirror = 0;
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
                g_SceneEventStep = 0x15;
            }
            break;
        case 21:
            func_801F4080();
            break;
        case 30:
            g_Actors[D_801F58D0].unk_7E += 1;
            g_Game.members[0].u.field.unk_122 += 1;
            g_SceneEventStep = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] == 0x1A) {
                UI_ModeSet(0);
                SND_StartDecrescendo(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 0x64, 0x20);
                g_SceneEventStep = 0x20;
            }
            break;
        case 32:
            if (!g_SysThreads[2].state) {
                g_AreaDrawFlags = 0;
                SND_SeqStop(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4]);
                SND_XAStartStream(6, 1);
                UI_MessageStartArea(0x1B);
                g_GameStateIndex = 2;
                g_SceneEventStep = 0x21;
            }
            break;
        case 33:
            if (g_GameStateIndex != 2 && (SND_XAIsIdle() & BYTE_MASK) != 0) {
                g_SceneEventStep = 0x22;
            }
            break;
        case 34:
            SYS_ClearFlag(g_SceneEventFlags, 0x41);
            Game_RequestAreaChange(0x4B, 0x198000, 0x1B8000, 0x83);
            g_SceneEventStep = 0x23;
            break;
        case 35:
            if (!g_SysThreads[2].state) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_ScriptVars[0] = 1;
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        default:
            break;
    }
    if ((u8)(g_SceneEventStep - 6) < 9) {
        func_801F4080();
    }
}
