#include "engine/slus/slus.h"

/* ticks the step timer at g_UIMessageState: at count zero it sets the count to one and increments the phase at +0x18; at
 * phase 7 it calls UI_MessageStartRequest for state 4 or 5, otherwise resets the cursor, state and count fields and masks
 * the +0x04 flags with 0xFFF3. */
MATCH void func_8015102C(void) {
    u8  one;
    u8  count;
    u8  phase;
    u16 flags;
    s32 cursor;

    count                  = g_UIMessageState.count;
    g_UIMessageState.count = count + 0xFF;
    if (count != 0) {
        return;
    }
    one                    = 1;
    g_UIMessageState.count = one;
    phase                  = g_UIMessageState.phase + 1;
    g_UIMessageState.phase = phase;
    if ((phase & BYTE_MASK) == 7) {
        if ((g_UIMessageState.state == 4) || (g_UIMessageState.state == 5)) {
            UI_MessageStartRequest();
        } else {
            g_UIMessageState.step   = 0;
            g_UIMessageState.state  = one;
            cursor                  = g_UIMessageState.cursor;
            g_UIMessageState.count  = 8;
            g_UIMessageState.scroll = 0;
            g_UIMessageState.index  = 0;
            g_UIMessageState.phase  = 0;
            g_UIMessageState.entry  = cursor;
            g_UIMessageState.flags &= 0xFFF3;
        }
    }
}
