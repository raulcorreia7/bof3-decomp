#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F650 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet10(void) {
    g_UIMessageRequest = g_AnswerMessages[20 + g_UIMessageWindow.selection_index];
}
