#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the 0x8017F644 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet7(void) {
    g_UIMessageRequest = g_AnswerMessages[14 + g_UIMessageWindow.selection_index];
}
