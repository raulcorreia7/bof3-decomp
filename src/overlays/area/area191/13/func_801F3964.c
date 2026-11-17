#include "area191_13.h"

MATCH void func_801F3964(void) {
    if (g_ScenarioState.scenario_id == 0xE) {
        if (SYS_TestFlag(g_SceneFlags, 5)) {
            return;
        }
    }
    func_801F39AC();
}
