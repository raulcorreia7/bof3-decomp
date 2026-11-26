#include "area143_13.h"

MATCH void func_801F3988(void) {
    s32 message;

    if (g_UiMessageChoice != 0) {
        message = 0x54;
    } else if (g_SaveData.found_genes != 0x3FFFF) {
        message = 0x53;
    } else {
        g_UiMessageRequest = MSG_AREA143_MASTER_TEACH_READY;
        return;
    }
    g_UiMessageRequest = message;
    g_MenuMasterStep   = 6;
}
