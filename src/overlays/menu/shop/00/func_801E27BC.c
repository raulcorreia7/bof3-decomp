#include "shop_00.h"

/* File-local declaration: the panel dispatch table selected by panel-task
 * byte 2 is owned by this translation unit. */

MATCH void func_801E27BC(void) {
    D_801E5D68[g_MenuCurrentPanel->unk_00[2]]();
}
