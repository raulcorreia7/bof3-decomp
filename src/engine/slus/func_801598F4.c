#include "engine/slus/slus.h"

/* dispatches through a stack copy of the five-entry table using the
 * menu panel task's state byte at +3.
 */
MATCH void func_801598F4(void) {
    struct CallbackTable5 table;

    table = D_80149B50;
    table.entry[g_MenuCurrentPanel->state]();
}
