#include "engine/slus/slus.h"

/* reports 1 when the staged area-script record index (work+0x4B)
 * already equals script_index; otherwise requests the record switch through
 * func_8014D6B8 and reports 0.
 */
MATCH u32 Script_Request(u8 script_index) {
    if (SELF(Actor)->script_record == script_index) {
        return 1;
    }
    Script_Select(script_index);
    return 0;
}
