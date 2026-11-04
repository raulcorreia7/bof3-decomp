#include "engine/slus/slus.h"

/* counts the staged entry byte at +0x4A down (0 while it survives); at expiry it re-arms it with 1 and
 * reports 1 when the stream index at +0x58 already selects the byte at +0x49, otherwise an opcode (>= 0x80) moves the
 * index to the operand's doubled value and reports 1; finally it stages the next entry through func_8014DB98.
 */
MATCH u8 func_8014DAEC(void) {
    u8  result;
    u8  count;
    u16 index;

    result             = 0;
    count              = g_SpadWork->unk_4A - 1;
    g_SpadWork->unk_4A = count;
    if ((count & BYTE_MASK) == 0) {
        index = g_SpadWork->script_pc;
        if ((index >> 1) == g_SpadWork->unk_49) {
            g_SpadWork->unk_4A = 1;
            return 1;
        }
        if (*(u8*)((u32)g_SpadWork->source_50 + index) >= 0x80) {
            g_SpadWork->script_pc = *(u8*)((u32)g_SpadWork->source_50 + index + 1) << 1;
            result                = 1;
        }
        func_8014DB98();
    }
    return result;
}
