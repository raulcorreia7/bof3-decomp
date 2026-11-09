#include "engine/slus/slus.h"

/* copies the eight-entry table at D_80149A7C to the stack and dispatches the entry selected by the selection byte g_UiWindowStep. */
MATCH void func_801510DC(void) {
    Table8 handlers;

    handlers = D_80149A7C;
    handlers.handlers[g_UiWindowStep]();
}
