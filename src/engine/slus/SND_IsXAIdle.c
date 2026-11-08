#include "engine/slus/slus.h"

/* tests the byte at 0x8014682D for zero.
 */
MATCH u8 SND_IsXAIdle(void) {
    return g_EmiServiceState == SND_XA_STATE_IDLE;
}
