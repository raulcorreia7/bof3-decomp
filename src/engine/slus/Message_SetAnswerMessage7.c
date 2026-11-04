#include "engine/slus/slus.h"

/* stores table entry D_801490C7 of the 0x8017F644 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage7(void) {
    g_MessageRequest = D_8017F628[14 + D_801490BC.selection_index];
}
