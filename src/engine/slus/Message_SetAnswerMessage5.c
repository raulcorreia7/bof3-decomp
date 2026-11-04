#include "engine/slus/slus.h"

/* stores table entry D_801490C7 of the 0x8017F63C row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage5(void) {
    g_MessageRequest = D_8017F628[10 + D_801490BC.selection_index];
}
