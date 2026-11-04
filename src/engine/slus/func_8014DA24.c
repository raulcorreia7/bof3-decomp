#include "engine/slus/slus.h"

/* counts the delay byte at +0x4A down (0 while it survives); at expiry with a zero stream index it reseeds
 * the index from twice the byte at +0x49 and reports 1, then steps the index back twice, staging the stream bytes and
 * the command's halfword from the table at +0x54 into +0x5A.
 */
MATCH u8 func_8014DA24(void) {
    u8  result;
    u8  count;
    u8  selected;
    u16 index;
    u16 prev;

    result             = 0;
    count              = g_SpadWork->unk_4A - 1;
    g_SpadWork->unk_4A = count;
    if ((count & BYTE_MASK) == 0) {
        if (g_SpadWork->script_pc == 0) {
            g_SpadWork->script_pc = g_SpadWork->unk_49 * 2;
            result                = 1;
        }

        index                 = g_SpadWork->script_pc;
        prev                  = index - 1;
        g_SpadWork->script_pc = prev;
        selected              = *(u8*)(g_SpadWork->source_50 + prev);
        index                 = index - 2;
        g_SpadWork->script_pc = index;
        g_SpadWork->unk_4A    = *(u8*)(g_SpadWork->source_50 + index);

        g_SpadWork->unk_5A = (u16) * (u16*)(g_SpadWork->range_54.table + selected * 2);
    }
    return result;
}
