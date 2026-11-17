#include "engine/slus/slus.h"
#include "common/copy.h"

/* snapshots the 21-entry local-mode callback table at g_UiLocalModes to
 * the stack and dispatches the entry selected by the current game-UI local
 * mode. UI_SetMode arms this loop through CbRegister.
 */
MATCH void UI_DispatchLocalMode(void) {
    Cpy16*       dst;
    const Cpy16* src;
    const Cpy16* end;
    u32          callbacks[21];

    dst = (Cpy16*)callbacks;
    src = (const Cpy16*)g_UiLocalModes;
    end = src + 5;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(u32*)(dst) = src->w[0];

    ((Callback)callbacks[g_UiLocalMode])();
}
