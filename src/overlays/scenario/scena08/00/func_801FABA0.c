#include "scena08_00.h"
#include "area/map.h"
#include "audio/audio.h"
#include "menu/gameui.h"
#include "psx/mem.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FABA0(void) {
    SpawnedActor* actor;
    SpawnedActor* spawned;
    u8*           character;
    u8            slot;
    u8            index;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SND_BGMStart(0x2B, 0x64, 0x40);
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step_05  = 1;
            /* fallthrough */
        case 1:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScenarioState.timer_06 = 0;
            g_ScenarioState.step_05  = 2;
            g_AreaDrawFlags          = AREA_DRAW_ALL_FLAGS;
            g_ScriptVars[0]          = 1;
            break;
        case 2:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != GAME_NONE) {
                actor               = &g_SpawnedActors[slot];
                actor->pos.x.fixed  = TO_COORD(0x8E);
                actor->header.flags = ACTOR_FLAG_IN_USE;
                actor->type         = 0x52;
                actor->header.mode  = 0;
                actor->pos.y.fixed  = TO_COORD(0x55);
                actor->pos.z.fixed  = TO_COORD(Area_HeightSample(actor->pos.x.fixed, TO_COORD(0x55)));
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step_05  = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            index                       = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = index;
            if (index != GAME_NONE) {
                spawned               = &g_SpawnedActors[index];
                spawned->header.flags = ACTOR_FLAG_IN_USE;
                spawned->type         = 0x52;
                spawned->header.mode  = 1;
            }
            g_ScenarioState.step_05 = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0x10) {
                break;
            }
            UI_ModeSet(4);
            g_ScenarioState.step_05 = 5;
            break;
        case 5:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags          = 0;
            g_ScenarioState.timer_06 = 0x40;
            /* FAKE: a writable table read keeps the slot load below the two stores, as retail has it. */
            SND_StartDecrescendo(((u8*)g_SelectionSepSlots)[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 0x64, 0x40);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SND_SeqStop(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4]);
            character                                     = &D_80181B17;
            g_Characters[*character].character_id         = 7;
            g_Characters[*character].base.surprise_chance = 0x37;
            g_Characters[*character].base.evasion         = 8;
            g_Characters[*character].base.accuracy        = 0x64;
            g_Characters[D_80181B18].character_id         = 8;
            g_Characters[D_80181B18].base.evasion         = 0xC;
            Scene_RunScenario(0);
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_GARR, TO_COORD(101), TO_COORD(8), FACING_UP);
            g_GamePrevSelection     = 0xFF;
            g_ScenarioState.step_05 = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_GARR, TO_COORD(100), TO_COORD(18), FACING_UP);
            g_GamePrevSelection = 0xFF;
            SYS_SetFlag(g_SceneFlags, 0);
            g_ScenarioState.step_05 = 8;
            break;
        case 8:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step_05  = 9;
            break;
        case 9:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SND_SEPlay(0x204);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            g_ScenarioState.step_05 = 0xA;
            break;
        case 10:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0]         = 0x17;
            g_ScenarioState.step_05 = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 0x1D) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_GARR, TO_COORD(100), TO_COORD(20), FACING_DOWN);
            SYS_SetFlag(g_SceneFlags, 1);
            g_ScenarioState.step_05 = 0xC;
            g_GameFlags |= 0x20;
            break;
        case 12:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}
