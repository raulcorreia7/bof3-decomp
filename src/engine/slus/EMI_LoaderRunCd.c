#include "engine/slus/slus.h"

typedef struct OverlayCallbackGroup {
    u32 values[4];
} OverlayCallbackGroup;

/* snapshots the target-local EMI callback table and invokes the
 * callback selected by the current loader mode.
 */
MATCH void EMI_LoaderRunCd(void) {
    OverlayCallbackGroup*       dst;
    const OverlayCallbackGroup* src;
    const OverlayCallbackGroup* end;
    u32                         callbacks[9];

    dst = (OverlayCallbackGroup*)callbacks;
    src = (const OverlayCallbackGroup*)g_EmiCdSteps;
    end = src + 2;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(u32*)(dst) = src->values[0];

    ((Callback)callbacks[D_8014648A])();
}
