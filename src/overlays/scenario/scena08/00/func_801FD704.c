/* FAKE: retail re-reads each scroll target right after storing it. */
#define FAKE_DECL_AREA_SCROLL_TARGET_VOLATILE
#define FAKE_DECL_AREA_SCROLL_TARGET_Y_VOLATILE
#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Step script: the party loads, the Rei collapse cutscene, the scripted battle and the chapter advance. */
MATCH void func_801FD704(void) {
    u8  slot;
    s32 x;
    s32 y;

    switch (g_ScenarioState.step_05) {
        case 0:
            Scene_SetupParty(0);
            EMI_PartyLoadCode(7, 8, 4);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_AreaScrollTargetX     = TO_COORD(23);
            g_PartyX                = TO_COORD(23);
            g_AreaScrollTargetY     = TO_COORD(15);
            g_PartyY                = TO_COORD(15);
            g_ScenarioState.step_05 = 2;
            g_AreaCameraStep        = g_RouteSpeedScale[5] * 8;
            break;
        case 2:
            if (!EMI_IsReady()) {
                break;
            }
            if (g_AreaCameraMoving != 0) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                SpawnedActor* actor = &g_SpawnedActors[slot];

                actor->header.flags = 1;
                actor->type         = 0x5F;
                actor->header.mode  = 8;
            }
            g_ScenarioState.timer_06 = 0x10;
            g_ScenarioState.step_05  = 100;
            break;
        case 100:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            EMI_PartyLoad(7, 8, 4, 0);
            g_ScenarioState.step_05 = 3;
            g_ScriptVars[0]++;
            break;
        case 3:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            if (!EMI_IsReady()) {
                break;
            }
            Scene_RunScenario(5);
            Scene_SetupParty(1);
            g_ScenarioState.step_05 = 4;
            g_ScriptVars[0]++;
            break;
        case 4:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                SpawnedActor* actor = &g_SpawnedActors[slot];

                actor->header.flags = 1;
                actor->type         = 0x60;
                actor->header.mode  = 0;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
            g_ScenarioState.timer_06 = 0xC;
            g_ScenarioState.step_05  = 5;
            break;
        case 5:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            g_ScenarioState.step_05 = 6;
            g_ScriptVars[0]++;
            break;
        case 6:
            if (g_ScriptVars[0] != 0x17) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_BGMFadeOut(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, 0x20);
            SCENARIO_MESSAGE_WAIT(MSG_SCENA08_009, 7);
            break;
        case 7: {
            u8* state = &g_GameStateIndex;
            u8* slots = (u8*)g_CharSlot;

            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            func_801FDF84();
            *state = 6;
            g_Characters[slots[CHAR_ID_RYU_ADULT]].party_flags |= 0x02;
            g_Characters[slots[CHAR_ID_REI]].party_flags |= 0x02;
            g_Characters[slots[CHAR_ID_REI]].hp = 0;
            g_Characters[slots[CHAR_ID_REI]].status |= 0x6000;
            g_ScenarioState.step_05 = 8;
            break;
        }
        case 8: {
            u8* state = &g_GameStateIndex;

            if (*state != 0) {
                break;
            }
            *state                  = 1;
            D_80148660              = 1;
            g_ScenarioState.step_05 = 9;
            break;
        }
        case 9:
            if (g_GameStateIndex != 0) {
                break;
            }
            Scene_SetupParty(2);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            func_801BFE34(TO_COORD(21), TO_COORD(25), 0x22);
            g_ScenarioState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x1A) {
                break;
            }
            Game_BattleStartScripted(0x22);
            g_ScenarioState.step_05 = 11;
            break;
        case 12:
            g_ScriptVars[0]++;
            Scene_SetupParty(3);
            g_ScenarioState.step_05 = 13;
            SYS_SetFlag(g_SceneFlags, 0x15);
            break;
        case 13:
            if (g_ScriptVars[0] != 0x1E) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step_05 = 14;
            break;
        case 14:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Scene_RunScenario(6);
            Game_RequestAreaChange(AREA_ID_MIKBA_CHECKPOINT, TO_COORD(17), TO_COORD(23), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
            g_GamePrevSelection      = 0xFF;
            g_ScenarioState.timer_06 = 0x78;
            g_ScenarioState.step_05  = 15;
            break;
        case 15:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            SND_BGMStart(0x73, BGM_CUE_LEVEL_DEFAULT, 0x20);
            UI_ModeSet(1);
            g_ScenarioState.step_05 = 16;
            g_ScriptVars[0]++;
            break;
        case 16:
            if (g_ScriptVars[0] != 0x3A) {
                break;
            }
            SND_BGMFadeOut(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            SND_XAStartStream(3, 1);
            g_ScenarioState.step_05 = 17;
            break;
        case 17:
            if ((u8)SND_XAIsIdle() == 0) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step_05 = 18;
            break;
        case 18:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA08_034, 19);
            break;
        case 19: {
            u8* state = &g_GameStateIndex;
            u8* slots = (u8*)g_CharSlot;

            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state = 6;
            g_Characters[slots[CHAR_ID_RYU_ADULT]].party_flags |= 0x02;
            g_Characters[slots[CHAR_ID_REI]].party_flags &= ~0x02;
            g_ScenarioState.step_05 = 20;
            break;
        }
        case 20:
            if (g_GameStateIndex != 0) {
                break;
            }
            SND_BGMStart(100, BGM_CUE_LEVEL_DEFAULT, 0x20);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
            x                   = g_AreaScrollTargetX;
            g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
            y                   = g_AreaScrollTargetY;
            g_ScriptVars[0]     = 0;
            Area_ScrollAdvance(Area_HeightSample(x, y));
            Area_InitMapRenderer();
            g_ScenarioState.step_05 = 21;
            break;
        case 21:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            Game_ClearScriptActive();
            Scene_RequestChapterAdvance();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}
