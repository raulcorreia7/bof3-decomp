#include "engine/slus/slus.h"

/* XA state: idle; clears the wait frames and the sync result. */
MATCH void SND_XAStateIdle(void) {
    g_XAWaitFrames = 0;
    g_XASyncResult = 0;
}
