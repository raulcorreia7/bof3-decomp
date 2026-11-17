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

    count                = g_MessageState.count;
    g_MessageState.count = count + 0xFF;
    if (count != 0) {
        return;
    }
    one                  = 1;
    g_MessageState.count = one;
    phase                = g_MessageState.phase + 1;
    g_MessageState.phase = phase;
    if ((phase & BYTE_MASK) == 7) {
        if ((g_MessageState.state == 4) || (g_MessageState.state == 5)) {
            Message_StartRequest();
        } else {
            g_MessageState.selection = 0;
            g_MessageState.state     = one;
            cursor                   = g_MessageState.cursor;
            g_MessageState.count     = 8;
            g_MessageState.scroll    = 0;
            g_MessageState.index     = 0;
            g_MessageState.phase     = 0;
            g_MessageState.entry     = cursor;
            g_MessageState.flags &= 0xFFF3;
        }
    }
}
