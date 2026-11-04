#include "game_00.h"

MATCH void Area_RunFrame(void) {
    func_801C57F4();
    func_8015A7E8();
    func_80199440();
    func_801A06D8();
    func_801527E4();
    Area_RunParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    GFX_UpdatePaletteAnimations();
    func_8019625C();
    Area_DrawScene();
}
