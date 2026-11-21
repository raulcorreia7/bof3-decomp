#include "engine/slus/slus.h"

/* latches the loader status, selecting the error status when the
 * recorded state is negative.
 */
MATCH void CD_OnSeek(void) {
    s32 state;

    state = D_8014648C;
    if (state < 0) {
        state = 1;
    } else {
        state = 4;
    }
    D_8014648A = state;
}
