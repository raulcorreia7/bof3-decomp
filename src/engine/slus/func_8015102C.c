#include "engine/slus/slus.h"

/* ticks the step timer at g_UiMessageState: at count zero it sets the count to one and increments the phase at +0x18; at
 * phase 7 it calls UI_MessageStartRequest for state 4 or 5, otherwise resets the cursor, state and count fields and masks
 * the +0x04 flags with 0xFFF3. */
MATCH void func_8015102C(void) {
    u8  one;
    u8  count;
    u8  phase;
    u16 flags;
    s32 cursor;

    count                  = g_UiMessageState.count;
    g_UiMessageState.count = count + 0xFF;
    if (count != 0) {
        return;
    }
    one                    = 1;
    g_UiMessageState.count = one;
    phase                  = g_UiMessageState.phase + 1;
    g_UiMessageState.phase = phase;
    if ((phase & BYTE_MASK) == 7) {
        if ((g_UiMessageState.state == 4) || (g_UiMessageState.state == 5)) {
            UI_MessageStartRequest();
        } else {
            g_UiMessageState.step   = 0;
            g_UiMessageState.state  = one;
            cursor                  = g_UiMessageState.cursor;
            g_UiMessageState.count  = 8;
            g_UiMessageState.scroll = 0;
            g_UiMessageState.index  = 0;
            g_UiMessageState.phase  = 0;
            g_UiMessageState.entry  = cursor;
            g_UiMessageState.flags &= 0xFFF3;
        }
    }
}
