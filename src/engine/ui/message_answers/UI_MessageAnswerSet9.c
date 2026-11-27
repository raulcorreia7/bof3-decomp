#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F64C row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet9(void) {
    g_UIMessageRequest = g_AnswerMessages[18 + g_UIMessageWindow.selection_index];
}
