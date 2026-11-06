#include "engine/slus/slus.h"

/* copies the six-entry table at D_80149AB4 to the stack and dispatches
 * the entry selected by the selection byte g_MessageChoiceMode.
 */
MATCH void func_801518F4(void) {
    Table6 handlers;

    handlers = D_80149AB4;
    handlers.handlers[g_MessageChoiceMode]();
}
