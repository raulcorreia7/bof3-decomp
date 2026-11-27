#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F83C8(void) {
    u8           index;
    PartyMember* work;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != 2) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(1);
                g_ScenarioState.step = 1;
            }
            break;
        case 1: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 3) {
                break;
            }
            *progress = 0;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            SYS_SetFlag(g_SceneFlags, 7);
            g_ScenarioState.step = 2;
            Game_RequestAreaChange(0x44, 0x300000, 0x198000, 0x82);
            g_GamePrevSelection = 0x7D;
            break;
        }
        case 2:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] == 3) {
                Scene_SetupParty(3);
                g_ScenarioState.step = 2;
            } else if (g_ScriptVars[0] == 0x14) {
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step = 6;
            break;
        case 6: {
            index                       = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = index;
            if (index != 0xFF) {
                g_SpawnedActors[index].header.flags               = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x8C;
            }
            index                       = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = index;
            if (index != 0xFF) {
                g_SpawnedActors[index].header.flags               = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x8B;
            }
            g_GameState = &g_Game.members[0];
            SELF_SET(&g_Game.members[0]);
            g_ScenarioState.step = 7;
            D_80145FA8 |= 0x40;
            break;
        }
        case 8:
            g_GameState = &g_Game.members[0];
            SELF_SET(&g_Game.members[0]);
            D_80145FA8 &= 0xBF;
            SND_SEPlay(0x201);
            SND_SeqFadeOut(0, 1, 4, 0x1E);
            g_ScenarioState.step = 9;
            break;
        case 9:
            SELF_SET(&g_Game.members[0]);
            SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();
            if (SELF(Actor)->param.actor_slot != 0xFF) {
                g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 6;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06       = 3;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].vx           = 0;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].selection    = 0x3A;
                work                                                        = SELF(PartyMember);
                g_SpawnedActors[SELF(Actor)->param.actor_slot].screen_x     = work->screen_x.value;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].screen_y     = work->screen_y.value;
                g_ScenarioState.step                                        = 0xA;
            }
            break;
        case 10:
            SND_XAStartStream(6, 1);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if ((SND_XAIsIdle() & 0xFF) == 0) {
                break;
            }
            UI_MessageStartArea(MSG_SCENA11_040);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0xC;
            break;
        case 12:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step = 0xD;
            Game_RequestAreaChange(0x44, 0x2E8000, 0x178000, 0x84);
            g_GamePrevSelection = 0x7C;
            break;
        case 0xD:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 0xF:
            g_GameState = &g_Game.members[0];
            SELF_SET(&g_Game.members[0]);
            D_80145FA8 &= 0xBF;
            SND_SeqFadeOut(0, 1, 4, 0x1E);
            Scene_SetupParty(5);
            g_ScenarioState.step = 0x10;
            break;
        case 0x10:
            SND_XAStartStream(5, 1);
            g_ScenarioState.step = 0x11;
            break;
        case 0x11:
            if ((SND_XAIsIdle() & 0xFF) == 0) {
                break;
            }
            g_ScriptVars[0]      = 2;
            g_ScenarioState.step = 0x12;
            break;
        case 0x12: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 5) {
                break;
            }
            *progress            = 0;
            g_ScenarioState.step = 0x13;
            SYS_SetFlag(g_SceneFlags, 8);
            Game_RequestAreaChange(0x44, 0x2E8000, 0x178000, 0x86);
            g_GamePrevSelection = 0x7C;
            break;
        }
        case 0x13:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            if ((Item_Add(ITEM_CATEGORY_ITEM, ITEM_VINEGAR, 4, 0) & 0xFF) == 0) {
                strncpy((char*)g_TextVariables[0], (char*)Item_GetRecord(ITEM_CATEGORY_ITEM, ITEM_VINEGAR), 12);
                D_801490E4[0] = 0;
                UI_MessageStartArea(MSG_SCENA11_051);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 0x14;
            } else {
                UI_MessageStartArea(MSG_SCENA11_050);
                g_GameStateIndex = 2;
                SND_SEPlay(0x106);
                g_ScenarioState.step = 0x14;
            }
            break;
        case 0x14:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScriptVars[0]      = 2;
            g_ScenarioState.step = 0x16;
            break;
        case 0x16:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 0x28: {
            u8* progress;

            if (g_GameStateIndex == 2) {
                break;
            }
            progress = &g_ScriptVars[0];
            if (*progress == 0xFF) {
                Game_ClearScriptActive();
                *progress                = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            } else {
                *progress = 0;
                Scene_SetupParty(9);
                g_ScenarioState.step = 0x29;
            }
            break;
        }
        case 0x29: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_ScenarioState.step = 0x2A;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            Game_RequestAreaChange(0x44, 0x300000, 0x198000, 0x88);
            g_GamePrevSelection = 0x7D;
            break;
        }
        case 0x2A:
            if (g_ScriptVars[0] == 3) {
                Scene_SetupParty(3);
                g_ScenarioState.step = 2;
            } else if (g_ScriptVars[0] == 0x14) {
                g_ScenarioState.step = 5;
            }
            break;
    }
}
