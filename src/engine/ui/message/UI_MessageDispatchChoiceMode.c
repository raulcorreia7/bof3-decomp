#include "engine/slus/slus.h"

/* copies the six-entry table at g_UIMessageChoiceModes to the stack and dispatches
 * the entry selected by the selection byte g_UIMessageChoiceMode.
 */
/* func_801518F4 */
MATCH void UI_MessageDispatchChoiceMode(void) {
    MessageChoiceSteps handlers;

    handlers = g_UIMessageChoiceModes;
    handlers.steps[g_UIMessageChoiceMode]();
}
