#include "engine/slus/slus.h"

/* copies the eight-entry table at g_MessageStates to the stack and dispatches the entry selected by the selection byte g_MessageState. */
/* func_801507BC */
MATCH void Message_DispatchState(void) {
    Table8 handlers;

    handlers = g_MessageStates;
    handlers.handlers[g_MessageState.state_00]();
}
