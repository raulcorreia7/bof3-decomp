#include "engine/slus/slus.h"

/* reports 1 when the staged area-script record index (work+0x4B)
 * already equals selector; otherwise requests the record switch through
 * func_8014D6B8 and reports 0.
 */
MATCH u32 Actor_RequestScript(u8 selector) {
    if (g_SpadWork->unk_4B == selector) {
        return 1;
    }
    Actor_SelectScript(selector);
    return 0;
}
