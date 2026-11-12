#include "batl_end_00.h"

/* Adds the battle's reward zenny a step at a time; a held input pays the rest at
 * once, and either branch clears the amount and advances the UI state. */
MATCH void func_801EF7B4(void) {
    if (g_InputHeld != 0 && EMI_IsReady()) {
        Party_AddZenny(g_Battle.outcome.reward_zenny, 0);
        g_Battle.outcome.reward_zenny = 0;
        g_Battle.ui_state += 1;
    } else if (g_Battle.outcome.reward_zenny - D_801463B0 > 0) {
        Party_AddZenny(D_801463B0, 0);
        g_Battle.outcome.reward_zenny -= D_801463B0;
    } else {
        Party_AddZenny(g_Battle.outcome.reward_zenny, 0);
        g_Battle.outcome.reward_zenny = 0;
        g_Battle.ui_state += 1;
    }
}
