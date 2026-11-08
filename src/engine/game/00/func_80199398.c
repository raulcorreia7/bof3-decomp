#include "game_00.h"

MATCH void func_80199398(void) {
    Area_UpdateCamera();
    Area_UpdateParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    Area_DrawScene();
    Menu_UpdatePanelTasks();
    Shop_DispatchStep();
}
