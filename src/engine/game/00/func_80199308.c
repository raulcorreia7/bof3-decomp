#include "game_00.h"

MATCH void func_80199308(void) {
    func_80199440();
    Area_StepCamera();
    func_80167910();
    Area_RunParty();
    func_801BDAB8();
    func_80167E00();
    Actor_DispatchAll();
    func_8019625C();
    Area_DrawScene();
}
