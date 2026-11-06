#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F64C row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage9(void) {
    g_MessageRequest = D_8017F628[18 + g_MessageWindow.selection_index];
}
