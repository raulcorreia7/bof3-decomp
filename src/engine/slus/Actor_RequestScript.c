#include "engine/slus/slus.h"

/* reports 1 when the staged area-script record index (work+0x4B) already equals selector. */
MATCH u32 Actor_RequestScript(u8 selector) {
    if (g_Task->unk_4B == selector) {
        return 1;
    }
    Actor_SelectScript(selector);
    return 0;
}
