#include "engine/slus/slus.h"

/* reports 1 when the staged area-script record index (work+0x4B)
 * already equals script_index; otherwise requests the record switch through
 * func_8014D6B8 and reports 0.
 */
MATCH u32 Actor_RequestScript(u8 script_index) {
    if (g_Task->unk_4B == script_index) {
        return 1;
    }
    Actor_SelectScript(script_index);
    return 0;
}
