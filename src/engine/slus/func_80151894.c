#include "engine/slus/slus.h"

/* counts g_MessageStateTimer down and, when it reaches zero, advances the mode byte,
 * the entry index and bit 2 of g_UiWindowChannel.
 */
MATCH void func_80151894(void) {
    u8  value;
    u8  mode;
    u8  index;
    int flags;
    u8  advance;

    value         = g_MessageStateTimer[0];
    g_MessageStateTimer[0] = value + 0xFF;
    if (value == 0) {
        advance = D_80148333[0] + 1;
        index   = g_UiWindowStep + 1;
        mode    = advance;
        flags   = g_UiWindowChannel;
        flags |= FRONTEND_FLAG_SELECTION;
        D_80148333[0]     = mode;
        g_UiWindowStep    = index;
        g_UiWindowChannel = flags;
    }
}
