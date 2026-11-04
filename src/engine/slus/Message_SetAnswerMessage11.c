#include "engine/slus/slus.h"

/* stores table entry D_801490C7 of the D_8017F654 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage11(void) {
    g_MessageRequest = D_8017F628[22 + D_801490BC.selection_index];
}
