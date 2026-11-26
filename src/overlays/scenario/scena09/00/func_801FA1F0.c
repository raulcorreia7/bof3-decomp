#include "scena09_00.h"
#include "sys/exe.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA1F0(void) {
    Actor* work;
    u8     i;
    s32    x;
    s32    y;

    switch (g_ScenarioState.step) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_035, 0xA);
            break;
        case 1:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_036, 0xA);
            break;
        case 2:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_037, 0xA);
            break;
        case 3:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_038, 0xA);
            break;
        case 4:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_039, 0xA);
            break;
        case 5:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_033, 0xA);
            break;
        case 6:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_034, 0xA);
            break;
        case 10:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 15:
            Scene_SetupParty(0);
            g_ScenarioState.step = 0x10;
            break;
        case 16:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x12);
            Game_ClearScriptActive();
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            SCENARIO_RETURN_TO_START();
            break;
        case 20:
            SND_SEPlay(0x206);
            g_AreaSceneMode = 3;
            Scene_SetupParty(2);
            g_ScenarioState.step = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 25:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_044, 0xA);
            break;
        case 30:
            g_ScenarioState.step = 0x1F;
            Game_RequestAreaChange(0x77, TO_COORD(9) + COORD_HALF, TO_COORD(52) + COORD_HALF, 0x83);
            break;
        case 31:
            g_GameFlags |= 8;
            UI_ModeSet(1);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            SND_SEPlay(0x207);
            g_AreaSceneMode      = 3;
            g_ScenarioState.step = 0x20;
            break;
        case 32:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            Game_BattleStartEncounter(TO_COORD(17) + COORD_HALF, TO_COORD(52) + COORD_HALF, 0x35);
            g_ScriptVars[0]      = 2;
            g_ScenarioState.step = 0x21;
            break;
        case 33:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] != 7) {
                    continue;
                }
                g_Self                        = (Actor*)&g_Game.members[i];
                SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();
                if (SELF(Actor)->param.actor_slot == GAME_NONE) {
                    continue;
                }
                g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 6;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06       = 2;
                work                                                        = SELF(Actor);
                g_SpawnedActors[work->param.actor_slot].vx                  = 0;
                g_SpawnedActors[work->param.actor_slot].selection           = 0x24;
                g_SpawnedActors[work->param.actor_slot].screen_x            = work->screen_x;
                g_SpawnedActors[work->param.actor_slot].screen_y            = work->screen_y;
                g_ScriptVars[0]                                             = 4;
            }
            g_ScenarioState.step = 0x22;
            break;
        case 34:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 2) {
                    UI_MessageStartArea(MSG_SCENA09_048);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 4) {
                    UI_MessageStartArea(MSG_SCENA09_047);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 8) {
                    UI_MessageStartArea(MSG_SCENA09_046);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 5) {
                    UI_MessageStartArea(MSG_SCENA09_045);
                }
            }
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 0x23;
            break;
        case 35:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            g_AreaSceneMode = 0;
            SND_SEPlay(0x208);
            g_ScenarioState.step = 0x24;
            break;
        case 36:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_ScriptVars[0] = 0;
            Game_BattleStartEncounter(TO_COORD(13) + COORD_HALF, TO_COORD(52) + COORD_HALF, 0x35);
            Game_BattleStartScripted(0x35);
            g_ScenarioState.step = 0x25;
            break;
        case 38:
            x                    = g_Game.members[0].pos.x.fixed;
            y                    = g_Game.members[0].pos.y.fixed;
            g_AreaCameraSpeed    = 0x20;
            g_ScenarioState.step = 0x27;
            g_AreaScrollTargetX  = x;
            g_AreaScrollTargetY  = y;
            break;
        case 39:
            if (g_AreaCameraMoving) {
                break;
            }
            Scene_SetupParty(4);
            g_ScenarioState.step = 0x28;
            break;
        case 40:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x17);
            g_GameFlags ^= 8;
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
    }
}
