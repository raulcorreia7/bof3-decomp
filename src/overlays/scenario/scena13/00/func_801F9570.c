#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9570(void) {
    u8* state;

    switch (g_ScenarioState.step_05) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA13_018, 1);
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 0x10) {
                D_801FBFEC = Actor_SpawnHelper(4, 5, D_80181B28[g_Game.members[0].chr.character_id], g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, g_Game.members[0].pos.z.fixed);
                g_ScenarioState.step_05 = 11;
            }
            break;
        case 11:
            if (!(g_SpawnedActors[D_801FBFEC].header.flags & 1)) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0xD);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 20:
            g_ScriptVars[0] = 0;
            func_8019FA28(0x56, TO_COORD(12), TO_COORD(9) + COORD_HALF, 3);
            g_GamePrevSelection     = 0xFF;
            g_ScenarioState.step_05 = 21;
            break;
        case 21:
            if (g_UiWindowEffectBusy == 0) {
                Area_CellSetPalette(0xC, 9);
                SCENARIO_MESSAGE_WAIT(MSG_SCENA13_002, 22);
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 7) {
                g_ScenarioState.step_05 = 23;
                g_AreaTileRemainderY -= 0x400;
            }
            break;
        case 23:
            if (g_ScriptVars[0] == 8) {
                SYS_SetFlag(g_SceneFlags, 0xE);
                func_8019FA28(0x58, TO_COORD(36), TO_COORD(32), 0x81);
                g_GamePrevSelection     = 0xFF;
                g_GameRequestType       = 1;
                g_ScenarioState.step_05 = 24;
            }
            break;
        case 24:
            if (g_UiWindowEffectBusy == 0) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA13_010, 25);
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[0] = 0;
                func_8019FA28(0x56, TO_COORD(16), TO_COORD(9) + COORD_HALF, 0x81);
                g_GamePrevSelection     = 0x5C;
                g_GameEntryMode         = 0;
                g_ScenarioState.step_05 = 26;
            }
            break;
        case 26:
            if (g_ScriptVars[0] == 0x18) {
                UI_ModeSet(0);
                SND_StartDecrescendo(0, 1, 100, 0x20);
                g_ScenarioState.step_05 = 27;
            }
            break;
        case 27:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                MESSAGE_START_WAIT(MSG_SCENA13_020);
                SND_SeqStop(0, 1);
                g_ScenarioState.step_05 = 28;
            }
            break;
        case 28:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                SYS_ThreadWait(1);
                *state                  = 6;
                g_ScenarioState.step_05 = 29;
            }
            break;
        case 29:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0] = 0;
                SYS_SetFlag(g_SceneFlags, 0xF);
                func_8019FA28(0x56, TO_COORD(16), TO_COORD(9) + COORD_HALF, 3);
                g_GameRequestType       = 0xFF;
                g_GameEntryMode         = 0xFF;
                g_ScenarioState.step_05 = 30;
            }
            break;
        case 30:
            if (g_GameStateIndex == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_ScenarioState.step_05 = 31;
            }
            break;
        case 31:
            if (g_UiWindowEffectBusy == 0) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
                g_GameFlags &= 0xFFF7;
            }
            break;
    }
}
