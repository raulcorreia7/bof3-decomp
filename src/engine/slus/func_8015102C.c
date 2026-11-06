#include "engine/slus/slus.h"

/* ticks the step timer at D_801490A0: at count zero it sets the count to one and increments the phase at
 * +0x18; at phase 7 it calls Message_StartRequest for state 4 or 5, otherwise resets the cursor, state and count fields and
 * masks the +0x04 flags with 0xFFF3.
 */
MATCH void func_8015102C(void) {
    u8  one;
    u8  count;
    u8  phase;
    u16 flags;
    s32 cursor;

    count               = D_801490A0.count_06;
    D_801490A0.count_06 = count + 0xFF;
    if (count != 0) {
        return;
    }
    one                 = 1;
    D_801490A0.count_06 = one;
    phase               = D_801490A0.phase_18 + 1;
    D_801490A0.phase_18 = phase;
    if ((phase & 0xFF) == 7) {
        if ((D_801490A0.state_00 == 4) || (D_801490A0.state_00 == 5)) {
            Message_StartRequest();
        } else {
            D_801490A0.selection_01 = 0;
            D_801490A0.state_00     = one;
            cursor                  = D_801490A0.cursor_10;
            D_801490A0.count_06     = 8;
            D_801490A0.scroll_28    = 0;
            D_801490A0.index_19     = 0;
            D_801490A0.phase_18     = 0;
            D_801490A0.entry_0C     = cursor;
            D_801490A0.flags_04 &= 0xFFF3;
        }
    }
}
