#include "engine/slus/slus.h"

/* tests the byte at 0x8014682D for zero.
 */
MATCH s32 SND_IsXaIdle(void) {
    return g_EmiServiceState == 0;
}
