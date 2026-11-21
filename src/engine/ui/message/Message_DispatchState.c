#include "engine/slus/slus.h"

/* copies the eight-entry table at g_MessageStateSteps to the stack and
 * dispatches the entry selected by the selection byte g_MessageState.
 */
/* func_801507BC */
MATCH void Message_DispatchState(void) {
    MessageStateSteps handlers;

    handlers = g_MessageStateSteps;
    handlers.steps[g_MessageState.state]();
}
