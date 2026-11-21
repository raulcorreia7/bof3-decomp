#include "scena08_00.h"
#include "area/map.h"
#include "audio/audio.h"
#include "menu/gameui.h"
#include "menu/message_ids.h"
#include "psx/mem.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FB270(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            *(u32*)g_ScriptVars = 0;
            func_801BE1B0(6);
            g_AreaScrollTargetX     = D_80145EC4;
            g_AreaScrollTargetY     = D_80145EC8;
            g_AreaCameraStep        = g_RouteSpeedScale[4] << 3;
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_PartyX       = g_AreaScrollTargetX;
            g_PartyY       = g_AreaScrollTargetY;
            g_ScrollHeight = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
            Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
            g_ScriptVars[0]         = 1;
            g_ScenarioState.step_05 = 2;
            break;
        case 2: {
            u8            slot;
            SpawnedActor* actor;

            if (g_ScriptVars[0] != 5) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != 0xFF) {
                actor               = &g_SpawnedActors[slot];
                actor->pos.x.fixed  = TO_COORD_HALF(21);
                actor->header.flags = ACTOR_FLAG_IN_USE;
                actor->type         = 0x51;
                actor->header.mode  = 0;
                actor->pos.y.fixed  = TO_COORD_HALF(65);
                actor->pos.z.fixed  = Area_SampleHeight(actor->pos.x.fixed, TO_COORD_HALF(65)) << 16;
            }
            g_ScenarioState.step_05 = 3;
            break;
        }
        case 3:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            g_ScenarioState.timer_06 = 0x20;
            g_ScenarioState.step_05  = 4;
            SND_StartDecrescendo(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 0x64, 0x20);
            break;
        case 4:
            if (g_ScenarioState.timer_06-- != 0) {
                break;
            }
            g_ScriptVars[0]++;
            func_801BFE34(0x1C8000, 0x418000, 0x20);
            SND_StopSequence(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4]);
            g_ScenarioState.step_05 = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            g_ScenarioState.timer_06 = 0x61;
            g_ScenarioState.step_05  = 6;
            break;
        case 6:
            if (g_ScenarioState.timer_06-- == 0) {
                g_ScenarioState.timer_06 = 0x20;
                g_ScriptVars[0]++;
                g_ScenarioState.step_05 = 7;
            }
            break;
        case 7:
            if (g_ScenarioState.timer_06-- == 0) {
                g_ScenarioState.step_05 = 8;
            }
            break;
        case 8:
            SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0x0A));
            g_ScenarioState.step_05 = 9;
            break;
        case 9:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x17) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_PauseBGM(0x6C);
            Message_StartAreaMessage(MSG_SCENA08_018);
            g_GameStateIndex        = 2;
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            SND_ResumeBGM(0x6C);
            SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0x0B));
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x19) {
                break;
            }
            func_801C7A54(0x20);
            g_ScenarioState.step_05 = 13;
            break;
        case 13:
            EMI_LoadArchive(EMI_SLOT_A108SE2);
            while (EMI_IsReady() == 0) {
                func_801992B8();
                SYS_ThreadWait(1);
            }
            func_801BE1B0(7);
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 15;
            break;
        case 14: {
            u8 slot;

            if (g_ScriptVars[0] != 0x23) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != 0xFF) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0x63;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step_05  = 16;
            break;
        }
        case 15:
            if (g_ScenarioState.timer_06-- != 0) {
                break;
            }
            SND_PlayBGM(0x6D, 0x64, 0x10);
            g_ScenarioState.timer_06 = 0xA;
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 17;
            break;
        case 16:
            if (g_ScenarioState.timer_06-- == 0) {
                g_ScenarioState.step_05 = 18;
            }
            break;
        case 17:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            SYS_SetFlag((u8*)&D_80145548, 3);
            SYS_SetFlag((u8*)&D_80145548, 0x10);
            SYS_SetFlag(g_SceneFlags, 4);
            D_80146258 &= ~GAME_FLAG_SCROLL_LOCK;
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 18:
            break;
    }
}
#else
INCLUDE_ASM(func_801FB270);
#endif
