#include "engine/slus/slus.h"

/* copies the six-entry table at g_MessageChoiceModes to the stack and dispatches
 * the entry selected by the selection byte g_MessageChoiceMode.
 */
MATCH void func_801518F4(void) {
    Table6 handlers;

    handlers = g_MessageChoiceModes;
    handlers.handlers[g_MessageChoiceMode]();
}
