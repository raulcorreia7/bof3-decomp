#include "engine/slus/slus.h"

/* dispatches through a stack copy of the three-entry D_80149B30 table, using
 * the menu panel task's byte at +2.
 */
MATCH void func_80158F80(void) {
    struct CallbackTable3 table;

    table = D_80149B30;
    table.entry[g_MenuCurrentPanel->unk_00[2]]();
}
