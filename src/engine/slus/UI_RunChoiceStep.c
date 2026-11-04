#include "engine/slus/slus.h"

/* dispatches the handler the pending step byte D_801490A3 selects
 * through the two-entry table stored on the stack, then counts the pending
 * halfword D_801490AA down unless it is 0xFFFF, and clears D_801490A2 when the
 * count reaches zero.
 */
MATCH void UI_RunChoiceStep(void) {
    Table2 table = {{func_801519F8, func_80151A48}};

    table.handlers[D_801490A3]();
    if ((u16)D_801490AA != 0xFFFFu) {
        D_801490AA -= 1;
    }
    if (D_801490AA == 0) {
        D_801490A2 = 0;
    }
}
