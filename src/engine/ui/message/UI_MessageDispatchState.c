#include "engine/slus/slus.h"

/* copies the eight-entry table at g_UiMessageStateSteps to the stack and
 * dispatches the entry selected by the selection byte g_UiMessageState.
 */
/* func_801507BC */
MATCH void UI_MessageDispatchState(void) {
    MessageStateSteps handlers;

    handlers = g_UiMessageStateSteps;
    handlers.steps[g_UiMessageState.state]();
}
