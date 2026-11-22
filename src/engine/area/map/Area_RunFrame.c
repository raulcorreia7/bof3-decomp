#include "engine/game/00/game_00.h"

MATCH void Area_RunFrame(void) {
    func_801C57F4();
    func_8015A7E8();
    Party_RunFrame();
    Actor_RunInteractions();
    Camera_Update();
    Area_UpdateParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    GFX_PaletteUpdateAnimations();
    func_8019625C();
    Area_SceneDraw();
}
