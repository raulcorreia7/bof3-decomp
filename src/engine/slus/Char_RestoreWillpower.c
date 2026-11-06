#include "engine/slus/slus.h"

/* advances the record byte toward its limit by delta, clamping
 * upward at the limit, and restoring the limit when delta is empty.
 */
MATCH s32 Char_RestoreWillpower(s32 character_index, s32 amount, s32 mode) {
    Character* rec;
    s32        cur;
    s32        limit;

    if ((mode & BYTE_MASK) == 0) {
        rec = &g_SaveData.characters[character_index & BYTE_MASK];
    } else {
        rec = (Character*)&D_80145F04[(character_index & BYTE_MASK) * 0x140];
    }
    cur = rec->willpower;
    if (cur == rec->stats.willpower) {
        return 0;
    }
    rec->willpower = (u8)(cur + amount);
    limit          = rec->stats.willpower;
    if (((u32)limit < (u32)((cur + amount) & BYTE_MASK)) || ((amount & BYTE_MASK) == 0)) {
        rec->willpower = limit;
    }
    return 1;
}
