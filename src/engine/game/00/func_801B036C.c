#include "game_00.h"

MATCH void func_801B036C(void) {
    if (!(g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) && (g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) && !(func_801C3790(1) & BYTE_MASK) &&
        !(func_801C37DC(1) & BYTE_MASK)) {
        if (func_801B544C() & BYTE_MASK) {
            g_Game.current->u.field.step.value = 0;
            return;
        }
        if ((g_Game.input != 0) && !(g_Characters[g_Game.current->character_index].status & STATUS_CONFUSED)) {
            g_Game.current->u.field.step.value = 0;
        }
        if (!(func_801B6674() & BYTE_MASK) && !(func_801B6258() & BYTE_MASK) && !(Game_LeaderSwitchRequest() & BYTE_MASK) && !(Game_MenuRequestField() & BYTE_MASK) &&
            !(Game_RequestPersonalAction() & BYTE_MASK) && !(Game_CameraLookRequest() & BYTE_MASK) && !(Game_SceneCameraRequest() & BYTE_MASK) && (g_Game.input != 0)) {
            Game_GetInput();
            SELF(Actor)->option_flags = 0;
            SELF(Actor)->unk_0A       = 2;
            SELF(Actor)->param.unk_0B = 0;
            Actor_RequestRoute(SELF(Actor)->direction);
            SELF(Actor)->header.step = 1;
        }
    }
}
