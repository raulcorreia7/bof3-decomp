#include "battle_03.h"

MATCH void func_801E57C8(void) {
    if (((g_BattleOutcome.result & BATTLE_RESULT_DEFEAT) != 0u) && (D_80143F04 == AREA_ID_DESERT_OF_DEATH_MAP)) {
        UI_SetMode(4u);
        g_BattleSubStep = (g_BattleSubStep + 1u);
    }
}
