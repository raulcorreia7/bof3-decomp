#include "batl_end_00.h"

/* Adds the battle's reward experience a step at a time; a held input pays the rest
 * at once, and either branch clears the amount and advances the UI state. */
MATCH void func_801EEF14(void) {
    if (g_InputHeld != 0 && EMI_IsReady()) {
        func_801DD59C(g_Battle.outcome.reward_exp);
        g_Battle.outcome.reward_exp = 0;
        g_Battle.ui_state += 1;
    } else if ((s32)g_Battle.outcome.reward_exp - D_801463B0 > 0) {
        func_801DD59C(D_801463B0);
        g_Battle.outcome.reward_exp -= D_801463B0;
    } else {
        func_801DD59C(g_Battle.outcome.reward_exp);
        g_Battle.outcome.reward_exp = 0;
        g_Battle.ui_state += 1;
    }
}
