#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the 0x8017F640 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet6(void) {
    g_UIMessageRequest = g_AnswerMessages[12 + g_UIMessageWindow.selection_index];
}
