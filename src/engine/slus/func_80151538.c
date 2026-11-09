#include "engine/slus/slus.h"

/* copies the six-entry table at D_80149A9C to the stack and dispatches the entry selected by the selection byte g_UiWindowStep. */
MATCH void func_80151538(void) {
    Table6 handlers;

    handlers = D_80149A9C;
    handlers.handlers[g_UiWindowStep]();
}
