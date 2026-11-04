#include "engine/slus/slus.h"

/* selects the CD-read completion mode from the latched sync status
 * and clears the retry flag on failure.
 */
MATCH void EMI_LoaderFinishRead(void) {
    u8 mode;

    if (D_8014648C < 0) {
        g_EmiStreamState = 0;
        mode             = 4;
    } else {
        mode = 8;
    }
    D_8014648A = mode;
}
