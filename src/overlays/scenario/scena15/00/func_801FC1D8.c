#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC1D8(void) {
    u8* state;
    u8* mode;
    u8  slot;
    u8  i;

    switch (g_ScenarioState.step) {
        case 0:
            Game_ClearScriptActive();
            Scene_SetupParty(0xF);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 5:
            Scene_SetupParty(0x10);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            D_801FE748 = Actor_FindFreeSpawned();
            if (D_801FE748 == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE748].header.flags = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[D_801FE748].type         = 0xA4;
            g_ScenarioState.step                     = 7;
            break;
        case 8:
            g_ScenarioState.step = 9;
            g_AreaDrawFlags      = g_AreaDrawFlags & ~AREA_DRAW_CELL_LAYERS;
            g_ScriptVars[0]      = g_ScriptVars[0] + 1;
            break;
        case 10:
            SND_BGMRequest(0x82);
            Scene_SetupParty(0x11);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            if (!EMI_IsReady()) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].pos.x.fixed  = 0x2F8000;
                g_SpawnedActors[slot].header.flags = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[slot].type         = 0x1D;
                g_SpawnedActors[slot].pos.y.fixed  = 0x278000;
                g_SpawnedActors[slot].pos.z.fixed  = TO_COORD(Area_HeightSample(g_SpawnedActors[slot].pos.x.fixed, 0x278000));
            }
            SND_BGMPlay(0x82, 0x64, 8);
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 0xC;
            break;
        case 12:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScenarioState.step = 0xD;
            g_ScriptVars[0]++;
            break;
        case 13:
            if (g_ScriptVars[0] != 0x1F) {
                break;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 0xE;
            break;
        case 14:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x12);
            Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD(23) + COORD_HALF, TO_COORD(33), 0x8C);
            g_GameRequestType    = 0xFF;
            g_ScenarioState.step = 0xF;
            break;
        case 15:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SCENARIO_MESSAGE_WAIT(MSG_SCENA15_043, 0x10);
            break;
        case 16:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            g_ScenarioState.step = 0x11;
            g_ScriptVars[0]++;
            break;
        case 17:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            if (g_ScenarioState.timer_06 < 0x20) {
                func_801FCA3C(0);
                g_ScenarioState.timer_06++;
                break;
            }
            func_801FCA3C(1);
            SND_StartDecrescendo(0, 0, 0x64, 8);
            g_ScenarioState.timer_06 = 0;
            g_ScenarioState.step     = 0x12;
            break;
        case 18:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_SeqStop(0, 0);
            UI_ModeSet(0xD);
            g_ScenarioState.step = 0x13;
            break;
        case 19:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0x14;
            break;
        case 20:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SCENARIO_MESSAGE_WAIT(MSG_SCENA15_045, 0x15);
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 0x16;
            break;
        case 22:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            D_801FE748 = Actor_FindFreeSpawned();
            if (D_801FE748 != GAME_NONE) {
                g_SpawnedActors[D_801FE748].header.flags = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[D_801FE748].type         = 0xA5;
            }
            g_ScenarioState.step = 0x17;
            break;
        case 24:
            if (!(g_PadStates[0].held & PADstart)) {
                break;
            }
            UI_ModeSet(0xD);
            g_ScenarioState.step = 0x19;
            break;
        case 25:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SND_Exit();
            SYS_ThreadReplace(SYS_StartFrontend);
            break;
        case 30:
            Scene_SetupParty(0x12);
            SND_BGMRequest(0xA2);
            g_ScenarioState.step = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] != 0x2A) {
                break;
            }
            for (i = 0; i < ACTOR_COUNT; i++) {
                if (func_801ACE9C(g_Actors[i].unk_2C) == 0x308) {
                    g_Actors[i].unk_77 = 0x24;
                    g_Actors[i].unk_7E = 0;
                    break;
                }
            }
            SYS_SetFlag(g_SceneFlags, 0x11);
            g_ScenarioState.step = 0x20;
            break;
        case 32:
            if (g_ScriptVars[0] != 0x31) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 0x21;
            break;
        case 33:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA15_101, 0x22);
            break;
        case 34:
            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            Scene_RunScenario(1);
            *state               = GAME_REQUEST_SHOP;
            g_ScenarioState.step = 0x23;
            break;
        case 35:
            mode = &g_GameStateIndex;
            if (*mode != GAME_REQUEST_IDLE) {
                break;
            }
            *mode                = GAME_REQUEST_MENU;
            D_80148660           = 1;
            g_ScenarioState.step = 0x24;
            break;
        case 36:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_MYRIA_STATION_MYRIA_FIGHT, TO_COORD(22), TO_COORD(18), 0x80);
            g_GameEntryMode          = 0xFF;
            g_GameRequestType        = 0xFF;
            g_GamePrevSelection      = 0xFF;
            D_801FE750               = 0;
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 0;
            break;
    }
}
