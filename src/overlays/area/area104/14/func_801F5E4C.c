#include "area104_14.h"

MATCH void func_801F5E4C(void) {
    s8* state;
    s8* step;
    s8* flags;
    u8* request;
    s8  actor_index;
    s32 message;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            request = &g_GameStateIndex;
            if (*request == GAME_REQUEST_IDLE) {
                Message_StartAreaMessage(1);
                *request = GAME_REQUEST_MESSAGE;
                (*state)++;
            }
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                Game_RequestAreaChange(AREA_ID_STEEL_BEACH_MAP, TO_COORD(25), TO_COORD(45), FACING_LEFT);
                g_GameFlags &= ~(GAME_FLAG_SCRIPT_ACTIVE | GAME_FLAG_MENU_LOCK);
                g_SceneEventMode = SCENE_EVENT_NONE;
                *state           = 0;
            }
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                flags = &state[0x63C];
                if (SYS_TestFlag(flags, 0x5B) == 0) {
                    SYS_SetFlag(flags, 0x5B);
                    message = 2;
                } else {
                    message = 3;
                }
                MESSAGE_START_WAIT(message);
                step = &g_SceneEventStep;
                (*step)++;
            }
            break;
        case 3:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
                actor_index = Actor_FindFreeSpawned();
                if (actor_index != (s8)GAME_NONE) {
                    g_SpawnedActors[actor_index].header.flags++;
                    g_SpawnedActors[actor_index].type               = 0x6A;
                    g_SpawnedActors[actor_index].layer              = 0x19;
                    g_SpawnedActors[actor_index].unk_0A             = 0;
                    g_SpawnedActors[actor_index].pos.x.part.integer = g_Game.members[0].pos.x.part.integer;
                    g_SpawnedActors[actor_index].pos.y.part.integer = g_Game.members[0].pos.y.part.integer;
                }
                SND_StopSequence(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence);
                SND_PlayBGM(0x94, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                g_SceneEventMode = SCENE_EVENT_NONE;
                *state           = 0;
            }
            break;
    }
}
