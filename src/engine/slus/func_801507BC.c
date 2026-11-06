#include "engine/slus/slus.h"

/* copies the eight-entry table at g_MessageStateHandlers to the stack and
 * dispatches the entry selected by the selection byte g_MessageState.
 */
MATCH void func_801507BC(void) {
    Table8 handlers;

    handlers = g_MessageStateHandlers;
    handlers.handlers[g_MessageState.state_00]();
}
