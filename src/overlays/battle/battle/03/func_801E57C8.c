#include "battle_03.h"

MATCH void func_801E57C8(void) {
    if (((g_BattleResult & BATTLE_RESULT_DEFEAT) != 0u) && (D_80143F04 == 189)) {
        UI_SetMode(4u);
        g_BattleSubStep = (g_BattleSubStep + 1u);
    }
}
