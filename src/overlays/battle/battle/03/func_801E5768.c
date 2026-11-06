#include "battle_03.h"

MATCH void func_801E5768(void) {
    if (((g_BattleResult & BATTLE_RESULT_DEFEAT) != 0u) && (D_80143F04 == AREA_ID_DESERT_OF_DEATH_MAP)) {
        g_SceneState.state_04 = 1u;
        g_SceneState.step_05  = 0x19u;
        Game_SetScriptActive();
        func_801DDF28();
    }
}
