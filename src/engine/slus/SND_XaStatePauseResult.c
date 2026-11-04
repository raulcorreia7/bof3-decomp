#include "engine/slus/slus.h"

/* steps the status counter and issues the pending CD command.
 */
MATCH void SND_XaStatePauseResult(void) {
    s8* flag;

    flag = &D_8014682E;
    if (*flag < 0) {
        g_EmiServiceState = 6;
        if ((((s16)D_80146820++ < 6) == 0) || (SND_HasXaCdError() != 0)) {
            g_EmiServiceState = 8;
        }
    } else if (*flag != 0) {
        D_8014682F        = 2;
        g_EmiServiceState = 0;
        D_8014681C        = 0;
        *flag             = 0;
        g_EmiStreamState  = 3;
        CdSyncCallback(0);
    }
}
