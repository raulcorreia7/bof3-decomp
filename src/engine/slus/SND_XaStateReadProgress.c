#include "engine/slus/slus.h"

/* Polls the pending dispatch timer, else advances the retry counter. */
/* polls the status flag and issues the pending CD command.
 */
MATCH void SND_XaStateReadProgress(void) {
    s32 wrap;
    s8* flag;

    flag = &D_8014682E;
    if (*flag < 0) {
        g_EmiServiceState = 3;
        if ((((s16)D_80146820++ < 6) == 0) || (SND_HasXaCdError() != 0)) {
            g_EmiServiceState = 8;
        }
    } else if (*flag != 0) {
        SND_FadeCdVolume(0x80);
        wrap = (u16)D_8014681E < 6U;
        D_8014681E += 1;
        if (wrap == 0) {
            g_EmiServiceState = 5;
            D_8014681E        = 0;
            D_8014681C        = 0;
            *flag             = 0;
            D_8014682F        = 1;
        }
    }
}
