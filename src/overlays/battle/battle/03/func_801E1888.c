#include "battle_03.h"

/* counts the work area's step byte down; at expiry it requests the queued battle message, adds the
 * follow-up when the message flag allows it and advances the step byte.
 */
MATCH void func_801E1888(void) {
    PartyBattler* work;
    u8            count;

    work  = g_SpadWork;
    count = work->word_08.byte.unk_09;
    if (count == 0) {
        func_801DD858(5);
        if ((g_GameState->flags_128.value & 2) && ((g_DragonForm & BYTE_MASK) != 4) &&
            ((u32)((short)g_DragonForm - 7) >= 2)) {
            func_801DD858(3);
        }
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    } else {
        g_SpadWork->word_08.byte.unk_09 = count - 1;
    }
    func_801DEE4C();
}
