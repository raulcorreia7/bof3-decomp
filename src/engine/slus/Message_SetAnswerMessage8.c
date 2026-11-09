#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F648 row in g_MessageRequest. */
MATCH void Message_SetAnswerMessage8(void) {
    g_MessageRequest = g_AnswerMessages[16 + g_MessageWindow.selection_index];
}
