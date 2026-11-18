#include "game_00.h"

/* func_80199308 */
MATCH void Game_RunSceneFrame(void) {
    Party_RunFrame();
    Area_UpdateCamera();
    func_80167910();
    Area_UpdateParty();
    func_801BDAB8();
    func_80167E00();
    Actor_DispatchAll();
    func_8019625C();
    Area_DrawScene();
}
