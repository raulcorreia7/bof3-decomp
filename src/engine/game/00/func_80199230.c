#include "game_00.h"

MATCH void func_80199230(void) {
    Game_RunScenarioEntry();
    Menu_UpdatePanelTasks();
    func_801C57F4();
    func_8015A7E8();
    func_80199440();
    func_801A06D8();
    Area_UpdateCamera();
    Area_UpdateParty();
    func_801BDAB8();
    func_801A0514();
    Actor_DispatchAll();
    GFX_UpdatePaletteAnimations();
    func_8019625C();
    Area_DrawScene();
}
