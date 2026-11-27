#include "engine/slus/slus.h"

/* copies the `value`-selected area-script record into `dst` through func_8014D54C and re-arms the staged
 * entry: the staged position at 0x58 is reused two entries back when the staged index (0x4B) already equals `value`,
 * otherwise `value` becomes the index and the position restarts at zero.
 */
MATCH void Script_Switch(u8 value, u8* dst, s32 size) {
    s32 current;

    Script_CopyRecord(value, dst, (u16)size);
    if (SELF(Actor)->script_record == value) {
        current = SELF(Actor)->script_pc - 2;
    } else {
        SELF(Actor)->script_record = value;
        current                    = 0;
    }
    Script_Seek(current);
}
