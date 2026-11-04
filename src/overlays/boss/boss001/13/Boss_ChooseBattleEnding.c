#include "boss001_13.h"
#include "work/state.h"

/* func_800C1FF8 */
MATCH void Boss_ChooseBattleEnding(void) {
    if (g_BattleResult & BATTLE_RESULT_DEFEAT) {
        g_SceneState.state_04 = 6;
        g_SceneState.step_05  = 0x32;
    } else {
        g_SceneState.step_05++;
    }
    func_801DDF28();
}
