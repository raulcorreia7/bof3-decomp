#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9A44(void) {
    u8   index;
    u32  angle;
    u32* angle_cell;
    u8*  progress;
    u16* countdown;

    switch (D_80146875) {
        case 0:
            SND_FadeOutBGM(g_SndBGMId, 0x64, 8);
            SND_PlayCue(0x208);
            SND_PlayCue(0x207);
            D_80146875 = 1;
            break;
        case 1:
            func_801F9E70(D_80147B5C & 0xFFF);
            D_80146875 = 2;
            break;
        case 2:
            angle_cell      = &D_80147B5C;
            angle           = *angle_cell;
            LOH(D_1F800000) = angle & 0xFFF;
            if (g_InputHeld & 0x2000) {
                angle += 0x10;
                *angle_cell = angle;
                func_801F9E70(angle & 0xFFF);
            } else if (g_InputHeld & 0x8000) {
                angle -= 0x10;
                *angle_cell = angle;
                func_801F9E70(angle & 0xFFF);
            }
            if (g_InputPressed & 0x40) {
                D_80146875 = 3;
            }
            break;
        case 3: {
            u32 turn = D_80147B5C & 0xFFF;

            LOH(D_1F800000) = turn;
            if (turn - 0x4A0 < 0x41) {
                D_80146875 = 0xA;
            } else {
                D_80146875 = 5;
            }
            break;
        }
        case 5:
            SND_PlayCue(0x20A);
            SND_PlayCue(0x209);
            SND_PlayBGM(g_SndBGMId, 0x6E, 0x20);
            D_80146876 = 0x30;
            D_80146875 = 6;
            break;
        case 6:
            countdown  = &D_80146876;
            *countdown = *countdown - 1;
            if (*countdown != 0) {
                break;
            }
            Game_ClearScriptActive();
            Scene_SetupParty(1);
            D_80146874 = 0;
            D_80146875 = 0;
            break;
        case 10:
            SND_PlayCue(0x20A);
            SND_PlayCue(0x209);
            D_80146876 = 0x1E;
            D_80146875 = 0xB;
            break;
        case 11:
            countdown  = &D_80146876;
            *countdown = *countdown - 1;
            if (*countdown != 0) {
                break;
            }
            Scene_SetupParty(2);
            Area_SetCellPalette(0xA, 8);
            D_80146875 = 0xC;
            break;
        case 12:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            index = Actor_FindFreeSpawned();
            if (index != GAME_NONE) {
                g_SpawnedActors[index].header.flags = 1;
                g_SpawnedActors[index].type         = 0x7F;
                g_SpawnedActors[index].pos.x.fixed  = 0x98000;
                g_SpawnedActors[index].pos.y.fixed  = 0x68000;
                g_SpawnedActors[index].pos.z.fixed  = TO_COORD(3840);
            }
            D_80146876 = 0x28;
            D_80146875 = 0xD;
            break;
        case 13:
            countdown  = &D_80146876;
            *countdown = *countdown - 1;
            if (*countdown != 0) {
                break;
            }
            g_ScriptVars[0] = 3;
            D_80146875      = 0xE;
            break;
        case 14:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_StartXAStream(5, 1);
            Message_StartAreaMessage(5);
            g_GameStateIndex = 2;
            D_80146875       = 0xF;
            break;
        case 15:
            if (SND_IsXAIdle() == 0) {
                break;
            }
            if (g_GameStateIndex == 2) {
                break;
            }
            SND_PlayBGM(g_SndBGMId, 0x6E, 0x20);
            progress   = &g_ScriptVars[0];
            D_80146875 = 0x10;
            *progress  = *progress + 1;
            break;
        case 16:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x10);
            D_80146874 = 0;
            D_80146875 = 0;
            break;
    }
}
