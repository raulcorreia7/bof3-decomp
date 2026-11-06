#include "engine/slus/slus.h"

/* copies the eight-entry table at D_80149A5C to the stack and
 * dispatches the entry selected by the selection byte g_MessageState.
 */
MATCH void func_801507BC(void) {
    Table8 handlers;

    handlers = D_80149A5C;
    handlers.handlers[g_MessageState.state_00]();
}
