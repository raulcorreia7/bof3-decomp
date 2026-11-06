#include "game_00.h"

MATCH void func_80199398(void) {
    Area_StepCamera();
    Area_RunParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    Area_DrawScene();
    Menu_RunPanelTasks();
    Shop_DispatchStep();
}
