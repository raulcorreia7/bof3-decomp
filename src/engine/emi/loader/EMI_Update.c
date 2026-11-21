/* dispatches to the mode handler selected by the flag.
 */
#include "engine/slus/slus.h"

MATCH void EMI_Update(void) {
    if (g_EmiStreamMode == 1) {
        EMI_UpdateStream();
    } else if (g_EmiStreamMode == 2) {
        SND_UpdateXA();
    }
}
