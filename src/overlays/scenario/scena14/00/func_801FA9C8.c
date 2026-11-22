#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Spawns the actor of `actor_type` on the ground at (TO_COORD_HALF(28), TO_COORD_HALF(38)). */
#define SCENE_SPAWN_ON_GROUND(actor_type)                                                                       \
    slot = Actor_FindFreeSpawned();                                                                             \
    if (slot != GAME_NONE) {                                                                                    \
        SpawnedActor* actor = &g_SpawnedActors[slot];                                                           \
        actor->pos.x.fixed  = TO_COORD_HALF(28);                                                                \
        actor->header.flags = 1;                                                                                \
        actor->type         = (actor_type);                                                                     \
        actor->pos.y.fixed  = TO_COORD_HALF(38);                                                                \
        actor->pos.z.fixed  = (Area_HeightSample(actor->pos.x.fixed, TO_COORD_HALF(38)) << 16) + TO_COORD(128); \
    }

/* The scena14 Eden scenes: the party setups that end each one, the Teepo fight's approach and the
 * party restore after it. */
MATCH void func_801FA9C8(void) {
    u8  slot;
    u8* state;

    switch (g_ScenarioState.step_05) {
        case 0:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x15);
            Scene_SetupParty(1);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 1:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x16);
            Scene_SetupParty(2);
            func_801F4400();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 2:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x17);
            Scene_SetupParty(3);
            func_801F4508();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 3:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x19);
            Scene_SetupParty(6);
            func_801F4674();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 4:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x1A);
            Scene_SetupParty(7);
            func_801F4764();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 5:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x1C);
            Scene_SetupParty(0);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 6:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_BGMFadeOut(g_SndBGMId, 100, 4);
            g_ScenarioState.timer_06 = 8;
            g_ScenarioState.step_05  = 7;
            break;
        case 7:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags          = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            g_ScriptVars[0]++;
            break;
        case 10:
            if (!EMI_IsReady()) {
                break;
            }
            Scene_SetupParty(3);
            SND_BGMPlay(0x9F, 100, 8);
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] != 0x19 || g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.timer_06 = 10;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step_05  = 12;
            break;
        case 12:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags         = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step_05 = 13;
            g_ScriptVars[0]++;
            break;
        case 13:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            func_801BFE34(TO_COORD_HALF(44), TO_COORD_HALF(39), 0x25);
            func_801C7A54(0x33);
            g_ScenarioState.step_05 = 14;
            break;
        case 15:
            Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD_HALF(32), TO_COORD_HALF(38), 0x89);
            g_GamePrevSelection     = 0xFF;
            g_ScenarioState.step_05 = 16;
            break;
        case 16:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Scene_SpawnActor(0x31, g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, g_AreaCameraAngle.vz, 0x14, 0);
            SND_BGMRequest(0x9F);
            g_ScenarioState.step_05 = 17;
            break;
        case 17:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SCENE_SPAWN_ON_GROUND(0x97);
            g_ScenarioState.step_05 = 18;
            break;
        case 18:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            g_ScenarioState.timer_06 = 0x78;
            g_ScenarioState.step_05  = 19;
            break;
        case 20:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            g_ScriptVars[0]++;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_034, 21);
            break;
        case 21:
            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            func_801C1DF0(0xB);
            SYS_ThreadWait(1);
            *state                  = 6;
            g_ScenarioState.step_05 = 22;
            break;
        case 22: {
            u8* index = &g_GameStateIndex;

            if (*index != 0) {
                break;
            }
            *index                  = 1;
            D_80148660              = 1;
            g_ScenarioState.step_05 = 23;
            break;
        }
        case 23:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_AreaDrawMode           = 4;
            D_8014933F               = 0;
            g_AreaCameraRefreshCount = 2;
            Scene_SetupParty(0xA);
            func_801BFE34(TO_COORD_HALF(37), TO_COORD_HALF(39), 0x22);
            for (g_ScratchPad.cells.bytes[0] = 1; g_ScratchPad.cells.bytes[0] < 8; g_ScratchPad.cells.bytes[0]++) {
                if (g_Characters[g_ScratchPad.cells.bytes[0]].party_flags & 1) {
                    g_Characters[g_ScratchPad.cells.bytes[0]].willpower = g_Characters[g_ScratchPad.cells.bytes[0]].stats.willpower;
                    g_Characters[g_ScratchPad.cells.bytes[0]].hp        = g_Characters[g_ScratchPad.cells.bytes[0]].stats.max_hp;
                    g_Characters[g_ScratchPad.cells.bytes[0]].ap        = g_Characters[g_ScratchPad.cells.bytes[0]].stats.max_ap;
                    g_Characters[g_ScratchPad.cells.bytes[0]].status    = 0;
                }
            }
            for (g_ScratchPad.cells.bytes[0] = 1; g_ScratchPad.cells.bytes[0] < g_PartySize; g_ScratchPad.cells.bytes[0]++) {
                g_Game.members[g_ScratchPad.cells.bytes[0]].chr = g_Characters[g_CharSlot[g_PartyFieldOrder[g_ScratchPad.cells.bytes[0]]]];
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            g_ScenarioState.timer_06 = 0x40;
            g_ScenarioState.step_05  = 24;
            SCENE_SPAWN_ON_GROUND(0x98);
            break;
        case 24:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            func_801C7A54(0x34);
            g_ScenarioState.step_05 = 25;
            break;
        case 26:
            g_ScriptVars[0]++;
            SYS_SetFlag(g_SceneFlags, 0x1F);
            Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD_HALF(32), TO_COORD_HALF(38), 3);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 30:
            SND_BGMPause(g_SndBGMId);
            SND_XAStartStream(2, 1);
            Item_VitalAdd(0xC);
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_042, 31);
            break;
        case 31:
            if (!SND_XAIsIdle() || g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SND_BGMResume(g_SndBGMId);
            g_ScenarioState.step_05 = 32;
            g_ScriptVars[0]++;
            break;
        case 32:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            func_801A78F8();
            SYS_SetFlag(g_SceneFlags, 0x31);
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}
