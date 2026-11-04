#include "engine/slus/slus.h"

/* copies the `value`-selected area-script record into `dst` through func_8014D54C and re-arms the staged
 * entry: the staged position at 0x58 is reused two entries back when the staged index (0x4B) already equals `value`,
 * otherwise `value` becomes the index and the position restarts at zero.
 */
/* func_8014D5F0 */
MATCH void Actor_SwitchScript(u8 value, u8* dst, s32 size) {
    s32 current;

    Actor_CopyScriptEntry(value, dst, (u16)size);
    if (g_SpadWork->unk_4B == value) {
        current = g_SpadWork->script_pc - 2;
    } else {
        g_SpadWork->unk_4B = value;
        current            = 0;
    }
    Actor_SeekScript((u16)current);
}
