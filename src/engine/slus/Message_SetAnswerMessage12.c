#include "engine/slus/slus.h"

/* stores table entry D_801490C7 of the D_8017F658 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage12(void) {
    g_MessageRequest = D_8017F628[24 + D_801490BC.selection_index];
}
