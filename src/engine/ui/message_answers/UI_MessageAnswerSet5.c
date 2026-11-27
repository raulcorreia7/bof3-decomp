#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the 0x8017F63C row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet5(void) {
    g_UIMessageRequest = g_AnswerMessages[10 + g_UIMessageWindow.selection_index];
}
