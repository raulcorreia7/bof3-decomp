#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the 0x8017F644 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet7(void) {
    g_UiMessageRequest = g_AnswerMessages[14 + g_UiMessageWindow.selection_index];
}
