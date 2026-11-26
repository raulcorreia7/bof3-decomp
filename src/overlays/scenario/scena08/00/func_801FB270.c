#include "scena08_00.h"
#include "area/map.h"
#include "audio/audio.h"
#include "menu/gameui.h"
#include "menu/message_ids.h"
#include "psx/mem.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Runs the scene script one step per frame, keyed on g_ScenarioState.step. */
MATCH void func_801FB270(void) {
    switch (g_ScenarioState.step) {
        case 0:
            *(u32*)g_ScriptVars = 0;
            func_801BE1B0(6);
            g_AreaScrollTargetX  = D_80145EC4;
            g_AreaScrollTargetY  = D_80145EC8;
            g_AreaCameraSpeed    = g_RouteSpeedScale[4] << 3;
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_PartyPos.x.fixed        = g_AreaScrollTargetX;
            g_PartyPos.y.fixed        = g_AreaScrollTargetY;
            g_PartyPos.z.part.integer = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
            Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY));
            g_ScriptVars[0]      = 1;
            g_ScenarioState.step = 2;
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
                actor->pos.z.fixed  = Area_HeightSample(actor->pos.x.fixed, TO_COORD_HALF(65)) << 16;
            }
            g_ScenarioState.step = 3;
            break;
        }
        case 3:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            g_ScenarioState.timer_06 = 0x20;
            g_ScenarioState.step     = 4;
            SND_StartDecrescendo(g_SelectionSepSlots[g_SndBGMId * 4], ((u8*)g_SelectionSequences)[g_SndBGMId * 4], 0x64, 0x20);
            break;
        case 4:
            if (g_ScenarioState.timer_06-- != 0) {
                break;
            }
            g_ScriptVars[0]++;
            func_801BFE34(0x1C8000, 0x418000, 0x20);
            SND_SeqStop(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4]);
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            g_ScenarioState.timer_06 = 0x61;
            g_ScenarioState.step     = 6;
            break;
        case 6:
            if (g_ScenarioState.timer_06-- == 0) {
                g_ScenarioState.timer_06 = 0x20;
                g_ScriptVars[0]++;
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_ScenarioState.timer_06-- == 0) {
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0A));
            g_ScenarioState.step = 9;
            break;
        case 9:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_ScriptVars[0]++;
            g_ScenarioState.step = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x17) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_BGMPause(0x6C);
            UI_MessageStartArea(MSG_SCENA08_018);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            SND_BGMResume(0x6C);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0B));
            g_ScriptVars[0]++;
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x19) {
                break;
            }
            func_801C7A54(0x20);
            g_ScenarioState.step = 13;
            break;
        case 14:
            EMI_ArchiveLoad(EMI_SLOT_A108SE2);
            while (EMI_IsReady() == 0) {
                func_801992B8();
                SYS_ThreadWait(1);
            }
            func_801BE1B0(7);
            g_ScriptVars[0]++;
            g_ScenarioState.step = 15;
            break;
        case 15: {
            SpawnedActor* record;
            u8            slot;

            if (g_ScriptVars[0] != 0x23) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != 0xFF) {
                record               = &g_SpawnedActors[slot];
                record->header.flags = 1;
                record->type         = 0x63;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 16;
            break;
        }
        case 16:
            if (g_ScenarioState.timer_06-- != 0) {
                break;
            }
            SND_BGMPlay(0x6D, 0x64, 0x10);
            g_ScenarioState.timer_06 = 0xA;
            g_ScriptVars[0]++;
            g_ScenarioState.step = 17;
            break;
        case 17:
            if (g_ScenarioState.timer_06-- == 0) {
                g_ScenarioState.step = 18;
            }
            break;
        case 18:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            SYS_SetFlag((u8*)&g_SaveData.found_genes, 3);
            SYS_SetFlag((u8*)&g_SaveData.found_genes, 0x10);
            SYS_SetFlag(g_SceneFlags, 4);
            D_80146258 &= ~GAME_FLAG_SCROLL_LOCK;
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}
