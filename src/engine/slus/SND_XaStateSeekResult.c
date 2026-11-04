#include "engine/slus/slus.h"

/* steps the pending dispatch timer, else arms the next mode.
 */

MATCH void SND_XaStateSeekResult(void) {
    if (D_8014682E < 0) {
        g_EmiServiceState = 1;
        if ((((s16)D_80146820++ < 6) == 0) || (SND_HasXaCdError() != 0)) {
            g_EmiServiceState = 8;
        }
    } else if (D_8014682E != 0) {
        g_EmiServiceState = 3;
        D_80146832        = 1;
        D_8014681C        = 0;
    }
}
