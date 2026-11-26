#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Spawns an actor of type 0x94 into the free g_SpawnedActors slot D_801FC4C0. */
#define SCENE_SPAWN_SLOT_ACTOR()                         \
    D_801FC4C0 = Actor_FindFreeSpawned();                \
    if (D_801FC4C0 != GAME_NONE) {                       \
        g_SpawnedActors[D_801FC4C0].header.flags = 1;    \
        g_SpawnedActors[D_801FC4C0].type         = 0x94; \
    }

/* The same spawn, started in header mode 3. */
#define SCENE_SPAWN_SLOT_ACTOR_MODE3()                   \
    D_801FC4C0 = Actor_FindFreeSpawned();                \
    if (D_801FC4C0 != GAME_NONE) {                       \
        g_SpawnedActors[D_801FC4C0].header.flags = 1;    \
        g_SpawnedActors[D_801FC4C0].type         = 0x94; \
        g_SpawnedActors[D_801FC4C0].header.mode  = 3;    \
    }

/* Requests the area change with no entry mode, request type or previous selection. */
#define SCENE_AREA_CHANGE(area, x, y, entry)           \
    Game_RequestAreaChange((area), (x), (y), (entry)); \
    g_GameEntryMode     = GAME_NONE;                   \
    g_GameRequestType   = GAME_NONE;                   \
    g_GamePrevSelection = GAME_NONE

/* Scene 14's event script: one case per g_ScenarioState.step. */
MATCH void func_801F9834(void) {
    switch (g_ScenarioState.step) {
        case 0:
            Game_SetScriptActive();
            Scene_SetupParty(0);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[3] != 0x14) {
                break;
            }
            SYS_SetFlag(g_SceneEventFlags, 0x4E);
            Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD(38), TO_COORD(54), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            if (g_SpawnedActors[D_801FC4C0].header.flags & 1) {
                break;
            }
            func_801FA904(D_801FC450, D_801FC458);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0]      = 0xA;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x31, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x1E, 0)) {
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_SpawnedActors[D_801FC4C0].header.flags & 1) {
                break;
            }
            g_ScriptVars[0]++;
            func_801FA904(D_801FC454, D_801FC460);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.step = 7;
            g_ScriptVars[0]++;
            break;
        case 7:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x12);
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 10:
            g_ScriptVars[0] = 0xF;
            Scene_SetupParty(5);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 0x12) {
                break;
            }
            g_ScenarioState.step = 0xC;
            for (g_ScratchPad.cells.bytes[0] = 0; g_ScratchPad.cells.bytes[0] < g_PartySize; g_ScratchPad.cells.bytes[0]++) {
                if (g_Game.members[g_ScratchPad.cells.bytes[0]].chr.character_id == CHAR_ID_REI) {
                    Scene_SetupParty(6);
                    return;
                }
            }
            Scene_SetupParty(7);
            break;
        case 12:
            if (g_ScriptVars[0] != 0x23) {
                break;
            }
            SCENE_SPAWN_SLOT_ACTOR();
            g_ScenarioState.timer_06 = 0x5A;
            g_ScenarioState.step     = 0xD;
            break;
        case 13:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScenarioState.step = 0xE;
            g_ScriptVars[0]++;
            break;
        case 14:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x13);
            Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BALIO_SUNDER, TO_COORD(30), TO_COORD(11), 0);
            g_GameRequestType    = GAME_NONE;
            g_ScenarioState.step = 0xF;
            break;
        case 15:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            g_ScenarioState.step = 0x10;
            break;
        case 16:
            if (!WINDOW_EFFECT_BUSY()) {
                g_ScenarioState.step = 0x11;
                g_ScriptVars[0]++;
            }
            /* fall through */
        case 17:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x80, 0);
            g_ScenarioState.step = 0x12;
            break;
        case 18:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            UI_ModeSet(0);
            SND_StartDecrescendo(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence, 0x64, 0x20);
            g_ScenarioState.step = 0x13;
            break;
        case 19:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SND_SeqStop(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence);
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_048, 0x14);
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.step = 0x15;
            break;
        case 21:
            SCENE_AREA_CHANGE(AREA_ID_MOUNT_MYRNEG, TO_COORD(3), TO_COORD(7), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
            g_ScenarioState.step = 0x16;
            break;
        case 22:
        case 28:
        case 34:
        case 40:
        case 46:
        case 52:
        case 58:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            func_801F7960();
            UI_ModeSet(1);
            g_ScenarioState.step++;
            break;
        case 23:
        case 29:
        case 35:
        case 41:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step++;
            break;
        case 24:
        case 30:
        case 36:
        case 42:
        case 48:
        case 54:
        case 60:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step++;
            break;
        case 25:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_039, 0x1A);
            break;
        case 26:
        case 32:
        case 38:
        case 44:
        case 50:
        case 56:
        case 62:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.step++;
            break;
        case 27:
            SCENE_AREA_CHANGE(AREA_ID_MAEKYSS_GORGE, TO_COORD(30), TO_COORD(54), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
            g_ScenarioState.step = 0x1C;
            break;
        case 31:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_065, 0x20);
            break;
        case 33:
            SCENE_AREA_CHANGE(AREA_ID_ANGEL_TOWER_GARR_FIGHT, TO_COORD_HALF(38), TO_COORD_HALF(67), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
            g_ScenarioState.step = 0x22;
            break;
        case 37:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_020, 0x26);
            break;
        case 39:
            SCENE_AREA_CHANGE(AREA_ID_MIKBA_CHECKPOINT, TO_COORD(17), TO_COORD(25), 0);
            g_ScenarioState.step = 0x28;
            break;
        case 43:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_039, 0x2C);
            break;
        case 45:
            SCENE_AREA_CHANGE(AREA_ID_MOUNT_ZUBLO_GISSHAN, TO_COORD(76), TO_COORD(31), 0);
            g_ScenarioState.step = 0x2E;
            break;
        case 47:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x32;
            g_ScenarioState.step     = 0x30;
            break;
        case 49:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_010, 0x32);
            break;
        case 51:
            SCENE_AREA_CHANGE(AREA_ID_CLIFF_GAIST, TO_COORD_HALF(31), TO_COORD_HALF(116), 0);
            g_ScenarioState.step = 0x34;
            break;
        case 53:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x28;
            g_ScenarioState.step     = 0x36;
            break;
        case 55:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_073, 0x38);
            break;
        case 57:
            SCENE_AREA_CHANGE(AREA_ID_DRAGNIER_ELDER_FIGHT, TO_COORD(35), TO_COORD_HALF(29), 0);
            g_ScenarioState.step = 0x3A;
            break;
        case 59:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 0x3C;
            break;
        case 61:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_073, 0x3E);
            break;
        case 63:
            Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD_HALF(6), TO_COORD_HALF(44), 0);
            g_GameEntryMode      = GAME_NONE;
            g_GamePrevSelection  = 8;
            g_ScenarioState.step = 0x40;
            break;
        case 64:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            SCENE_SPAWN_SLOT_ACTOR_MODE3();
            g_Game.members[1].header.flags |= ACTOR_FLAG_HIDDEN;
            g_Game.members[2].header.flags |= ACTOR_FLAG_HIDDEN;
            SND_SEPlay(0x208);
            g_ScenarioState.step = 0x41;
            break;
        case 65:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            SCENE_SPAWN_SLOT_ACTOR_MODE3();
            SND_SEPlay(0x208);
            g_ScenarioState.step = 0x42;
            break;
        case 66:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            SCENE_SPAWN_SLOT_ACTOR_MODE3();
            g_Game.members[0].header.flags |= ACTOR_FLAG_HIDDEN;
            SND_SEPlay(0x208);
            g_ScenarioState.step = 0x43;
            break;
        case 67:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_RYU_DREAM_FIRST, TO_COORD_HALF(95), TO_COORD_HALF(10), 0);
            g_GameRequestType    = 0xE;
            g_GamePrevSelection  = GAME_NONE;
            g_ScenarioState.step = 0x44;
            break;
        case 68:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            if (g_SpawnedActors[D_801FC4C0].header.flags & 1) {
                break;
            }
            SND_BGMRequest(0x50);
            g_ScenarioState.step = 0x45;
            g_ScriptVars[0]++;
            break;
        case 69:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x13, -0x344, g_AreaCameraAngle.vy, 0x34A, 0x20, 0)) {
                g_ScenarioState.step = 0x46;
            }
            break;
        case 70:
            if (g_SpawnedActors[D_801FC4C0].header.flags & 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x14);
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 0x47;
            break;
        case 71:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x20, 0)) {
                g_ScenarioState.step = 0x48;
                g_ScriptVars[0]++;
            }
            break;
        case 72:
            if (g_SpawnedActors[D_801FC4C0].header.flags & 1) {
                break;
            }
            g_ScenarioState.step = 0x49;
            g_ScriptVars[0]++;
            break;
        case 73:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SND_BGMPlay(0x50, 0x64, 8);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}
