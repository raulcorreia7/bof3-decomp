#include "battle_03.h"

/* with the setup flag set and no pending slot, asks the selection helper for a state and advances the
 * selection stage to it, clearing the state byte when the helper accepts.
 */
MATCH void func_801D4028(void) {
    u8 next;

    if ((g_BattleState & BATTLE_STATE_EFFECT_PLAYING) != 0) {
        if (D_801463C2 == 0) {
            if ((func_800AA8FC() & 0xFF) != 0) {
                g_BattleRowCursor = 0;
                next              = g_BattleSubStep + 1;
            } else {
                next = 2;
            }
            g_BattleSubStep = next;
        }
    }
}
