#include "engine/slus/slus.h"

/* copies the six-entry table at g_MessageChoiceModes to the stack and dispatches
 * the entry selected by the selection byte g_MessageChoiceMode.
 */
/* func_801518F4 */
MATCH void Message_DispatchChoiceMode(void) {
    MessageChoiceSteps handlers;

    handlers = g_MessageChoiceModes;
    handlers.steps[g_MessageChoiceMode]();
}
