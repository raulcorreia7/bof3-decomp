#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7F08(void) {
    u8  index;
    u8* name;
    u32 roll;

    switch (g_SceneState.step_05) {
        case 0:
            if (D_80145F09 != 6) {
                g_SceneState.step_05 = 0x32;
                break;
            }
            index                       = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = index;
            if (index == 0xFF) {
                break;
            }
            g_SpawnedActors[index].header.flags                      = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type        = 0x34;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].pos.x.fixed = TO_COORD(37);
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].pos.y.fixed = TO_COORD(11);
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].pos.z.fixed = TO_COORD(1280);
            roll                                                     = rand() & 0xF;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.mode = D_801FAECC[roll];
            switch (D_801FAECC[roll]) {
                case 0:
                    g_SceneState.step_05 = 0x32;
                    break;
                case 2:
                    g_SceneState.step_05 = 1;
                    break;
                case 4:
                    g_SceneState.step_05 = 0x32;
                    break;
                case 5:
                    func_801F82D8(g_ScratchPad.cells.bytes[0]);
                    g_SceneState.step_05 = 5;
                    break;
            }
            break;
        case 1:
            TASK_SET(&g_Game.members[0]);
            g_GameState = &g_Game.members[0];
            func_801C308C(0);
            Char_LoseHP(1, 6);
            Message_Request(MSG_217);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_SceneState.step_05 = 0x32;
            break;
        case 5:
            if ((Item_Add(0, 0x23, 9, 0) & 0xFF) == 0) {
                name = Item_GetRecord(0, 0x23);
                strncpy((char*)g_TextVariables[0], (char*)name, 12);
                D_801490E4[0] = 0;
                Message_Request(MSG_003);
                g_GameStateIndex     = 2;
                g_SceneState.step_05 = 2;
            } else {
                Message_StartAreaMessage(MSG_066);
                g_GameStateIndex     = 2;
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_GameStateIndex == 2) {
                break;
            }
            SND_PlayCue(0x106);
            g_SceneState.step_05 = 0x32;
            break;
        case 0x14:
            if (D_80145F09 != 7) {
                g_SceneState.step_05 = 0x32;
                break;
            }
            SND_PlayCue(0x106);
            Message_StartAreaMessage(MSG_000);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 0x15;
            break;
        case 0x15:
            if (g_GameStateIndex == 2) {
                break;
            }
            Item_Add(0, 0x56, 1, 0);
            g_SceneState.step_05 = 0x32;
            break;
        case 0x32:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
