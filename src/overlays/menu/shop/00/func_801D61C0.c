#include "shop_00.h"

/* File-local declarations: frontend flag word, party-size byte, party pointer
 * table, and helpers owned by this target or the executable overlay. */

MATCH void func_801D61C0(void) {
    s16 value;
    s16 i;
    s16 next;

    if (SYS_TestFlag(g_SceneEventFlags, 119) != 0) {
        g_MenuStep.sub_step = 6;
        Message_StartAreaMessage(239);
        return;
    }
    if (g_SceneState.scenario_id != 0xE || SYS_TestFlag(*g_SceneFlags, 5) == 0) {
        SYS_SetFlag(g_SceneEventFlags, 119);
    }
    i = 0;
    do {
        value         = SsIsEos(0, i);
        D_801E6100[i] = value;
        if (value != 0) {
            SsSepPause(0, i);
            /* FAKE: the order fence keeps the next-value increment in
             * the cue call's delay slot. */
            FAKE_ORDER_FENCE();
        }
        next = i + 1;
        i    = next;
    } while (next < 4);
    UI_SetMode(UI_MODE_FADE_OUT);
    {
        u8* state;

        state = &g_MenuStep.sub_step;
        *state += 1;
    }
}
