#include "engine/slus/slus.h"

/* The copy unit the retail block move works in: 16 bytes per iteration. */
typedef struct {
    u32 values[4];
} GameUICallbackGroup;

/* snapshots the 21-entry local-mode callback table at g_UiLocalModeFuncs to
 * the stack and dispatches the entry selected by the current game-UI local
 * mode. UI_SetMode arms this loop through CbRegister.
 */
MATCH void UI_DispatchLocalMode(void) {
    GameUICallbackGroup*       dst;
    const GameUICallbackGroup* src;
    const GameUICallbackGroup* end;
    u32                        callbacks[21];

    dst = (GameUICallbackGroup*)callbacks;
    src = (const GameUICallbackGroup*)g_UiLocalModeFuncs;
    end = src + 5;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(u32*)(dst) = src->values[0];

    ((Callback)callbacks[g_UiLocalMode])();
}
