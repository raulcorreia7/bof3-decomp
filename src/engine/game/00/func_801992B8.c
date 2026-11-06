#include "game_00.h"

MATCH void func_801992B8(void) {
    Area_StepCamera();
    Area_RunParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    func_8019625C();
    Area_DrawScene();
}
