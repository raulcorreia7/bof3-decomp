#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F65C row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet13(void) {
    g_UIMessageRequest = g_AnswerMessages[26 + g_UIMessageWindow.selection_index];
}
