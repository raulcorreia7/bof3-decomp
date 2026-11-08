#include "battle_03.h"

MATCH void func_801E57C8(void) {
    if (((g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) != 0u) && (D_80143F04 == AREA_ID_DESERT_OF_DEATH_MAP)) {
        UI_SetMode(4u);
        g_Battle.phase.sub_step = (g_Battle.phase.sub_step + 1u);
    }
}
