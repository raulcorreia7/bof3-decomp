#include "engine/slus/slus.h"

/* copies the eight-entry table at g_UIMessageStateSteps to the stack and
 * dispatches the entry selected by the selection byte g_UIMessageState.
 */
/* func_801507BC */
MATCH void UI_MessageDispatchState(void) {
    MessageStateSteps handlers;

    handlers = g_UIMessageStateSteps;
    handlers.steps[g_UIMessageState.state]();
}
