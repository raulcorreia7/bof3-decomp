#include "engine/slus/slus.h"
#include "common/copy.h"

/* snapshots the target-local EMI callback table and invokes the
 * callback selected by the current loader mode.
 */
MATCH void CD_Update(void) {
    Cpy16*       dst;
    const Cpy16* src;
    const Cpy16* end;
    u32          callbacks[9];

    dst = (Cpy16*)callbacks;
    src = (const Cpy16*)g_CdSteps;
    end = src + 2;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(u32*)(dst) = src->w[0];

    ((Callback)callbacks[D_8014648A])();
}
