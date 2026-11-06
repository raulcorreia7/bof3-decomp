#include "engine/slus/slus.h"

/* ticks the step timer at g_MessageState: at count zero it sets the count to one and increments the phase at +0x18; at
 * phase 7 it calls Message_StartRequest for state 4 or 5, otherwise resets the cursor, state and count fields and masks
 * the +0x04 flags with 0xFFF3. */
MATCH void func_8015102C(void) {
    u8  one;
    u8  count;
    u8  phase;
    u16 flags;
    s32 cursor;

    count                   = g_MessageState.count_06;
    g_MessageState.count_06 = count + 0xFF;
    if (count != 0) {
        return;
    }
    one                     = 1;
    g_MessageState.count_06 = one;
    phase                   = g_MessageState.phase_18 + 1;
    g_MessageState.phase_18 = phase;
    if ((phase & BYTE_MASK) == 7) {
        if ((g_MessageState.state_00 == 4) || (g_MessageState.state_00 == 5)) {
            Message_StartRequest();
        } else {
            g_MessageState.selection_01 = 0;
            g_MessageState.state_00     = one;
            cursor                      = g_MessageState.cursor_10;
            g_MessageState.count_06     = 8;
            g_MessageState.scroll_28    = 0;
            g_MessageState.index_19     = 0;
            g_MessageState.phase_18     = 0;
            g_MessageState.entry_0C     = cursor;
            g_MessageState.flags_04 &= 0xFFF3;
        }
    }
}
