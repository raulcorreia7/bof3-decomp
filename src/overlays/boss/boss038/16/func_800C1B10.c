#include "boss038_16.h"
#include "work/state.h"

MATCH void func_800C1B10(void) {
    if (g_BattleResult & BATTLE_RESULT_VICTORY) {
        g_ScriptVars[0]      = 5;
        g_SceneState.step_05 = 0x20;
        g_SndBgmId           = 0x77;
        func_801DDED8();
        return;
    }
    func_801DDF00();
}
