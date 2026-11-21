#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the 0x8017F640 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet6(void) {
    g_UiMessageRequest = g_AnswerMessages[12 + g_UiMessageWindow.selection_index];
}
