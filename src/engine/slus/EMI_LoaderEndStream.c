#include "engine/slus/slus.h"

/* selects EMI loader mode 6 and phase 2, then clears its busy flag.
 */
MATCH void EMI_LoaderEndStream(void) {
    D_8014648A       = 6;
    g_EmiStreamState = 0;
    D_8014648B       = 2;
}
