#include "battle_15.h"

/* @returns whether the bytes at offsets 0x86/0x87 of g_GameState select
 * compare_value (masked); only checks when (battler_index & 0xFF) < 3.
 */
MATCH bool func_800A3638(s32 battler_index, s32 compare_value) {
    volatile u8* entry;
    s32          compare_byte;

    compare_byte = compare_value & 0xFF;
    if ((battler_index & 0xFF) < 3U) {
        entry = (u8*)(g_GameState);
        if (*(entry + 0x86) == compare_byte || *(entry + 0x87) == compare_byte) {
            return false;
        }
    }
    return true;
}
