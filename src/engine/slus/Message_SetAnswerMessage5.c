#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the 0x8017F63C row in g_MessageRequest. */
MATCH void Message_SetAnswerMessage5(void) {
    g_MessageRequest = g_AnswerMessages[10 + g_MessageWindow.selection_index];
}
