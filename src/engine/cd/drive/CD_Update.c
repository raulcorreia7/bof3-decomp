#include "engine/slus/slus.h"
#include "common/copy.h"

/* snapshots the target-local EMI callback table and invokes the
 * callback selected by the current loader mode.
 */
MATCH void CD_Update(void) {
    Cpy16*       dst;
    const Cpy16* src;
    const Cpy16* end;
    Callback     callbacks[CD_STATE_COUNT];

    dst = (Cpy16*)callbacks;
    src = (const Cpy16*)g_CdStateHandlers;
    end = src + 2;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(u32*)(dst) = src->w[0];

    callbacks[g_CdState]();
}
