#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9338(void) {
    switch (g_ScenarioState.step) {
        case 0:
            Scene_SetupParty(0);
            g_ScriptVars[0]      = 1;
            g_ScenarioState.step = 1;
            break;

        case 1: {
            u8 slot;

            if (g_ScriptVars[0] == 0x28) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x14;
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
                }
                g_ScenarioState.step = 2;
            }
            break;
        }

        case 2: {
            u8 slot;

            if (g_ScriptVars[0] == 0x29) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x14;
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
                }
                g_ScenarioState.step = 3;
            }
            break;
        }

        case 3: {
            u8 slot;

            if (g_ScriptVars[0] == 0x2A) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x14;
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
                }
                g_ScenarioState.step = 4;
            }
            break;
        }

        case 4:
            if (g_ScriptVars[0] == 0x32) {
                Char_AbilityAdd(0x97, g_CharSlot[0], 0, 0);
                SYS_SetFlag(&g_SaveData.found_genes, 0);
                SYS_SetFlag(g_SceneFlags, 1);
                Game_RequestAreaChange(AREA_ID_WYNDIA_WORLD_MAP, TO_COORD(0x28), TO_COORD(0x35), 0x86);
                g_GamePrevSelection  = 0x2F;
                g_GameRequestType    = 0xFF;
                g_ScenarioState.step = 5;
            }
            break;

        case 5: {
            u8 slot;

            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x31A;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x360;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0xF0;
            }
            g_ScenarioState.timer_06 = 0x20;
            g_ScenarioState.step     = 6;
            break;
        }

        case 6:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06 -= 1;
            } else {
                g_ScenarioState.step = 7;
            }
            break;

        case 7:
            if (g_ScriptVars[0] == 2) {
                SYS_SetFlag(g_SceneFlags, 2);
                g_GameFlags |= 0x80;
                Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE, TO_COORD(0x29), TO_COORD(0x27), 5);
                g_GameRequestType        = 0xFF;
                g_GameEntryMode          = 0;
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
