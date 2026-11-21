#include "engine/game/00/game_00.h"

MATCH void Area_RunLoadingFrame(void) {
    Camera_Update();
    Area_UpdateParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    func_8019625C();
    Area_DrawScene();
}
