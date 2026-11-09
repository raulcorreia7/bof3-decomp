/* dispatches to the mode handler selected by the flag. */
#include "engine/slus/slus.h"

MATCH void EMI_Update(void) {
    if (g_EmiServiceMode == 1) {
        EMI_UpdateStream();
    } else if (g_EmiServiceMode == 2) {
        SND_UpdateXA();
    }
}
