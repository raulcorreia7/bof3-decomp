#include "engine/slus/slus.h"

/* true when the XA state machine is idle. */
MATCH u8 SND_XAIsIdle(void) {
    return g_EmiServiceState == SND_XA_STATE_IDLE;
}
