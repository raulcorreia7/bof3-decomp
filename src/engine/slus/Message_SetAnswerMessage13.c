#include "engine/slus/slus.h"

/* stores table entry D_801490C7 of the D_8017F65C row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage13(void) {
    g_MessageRequest = D_8017F628[26 + D_801490BC.selection_index];
}
