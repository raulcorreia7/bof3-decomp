#include "battle_03.h"

/* arms every active local battler's queued action, clears the battle
 * state bundle, and advances the shared scene counter.
 */
/* func_801D7350 */
MATCH void Battle_WriteBackParty(void) {
    s32           i;
    u32           index;
    u32           off;
    u32           rec;
    u8            value;
    volatile u16* counter;
    u16           count;

    func_800ACF80();
    i = 0;
    func_801E5A38();
    if (g_Battle.party_count != 0) {
        do {
            index = i & BYTE_MASK;
            off   = index * BATTLE_PARTY_STRIDE;
            if ((g_Game.members[index].chr.status & STATUS_KO) != 0u) {
                rec                         = g_Game.members[index].character_index;
                value                       = g_Characters[rec].fatigue;
                g_Characters[rec].hp        = 1;
                g_Characters[rec].willpower = 1;
                if (value < 5u) {
                    g_Characters[rec].fatigue = value + 1;
                }
                g_Characters[rec].status &= ~STATUS_KO;
                g_Characters[rec].unk_07 &= 0xFBu;
                Char_RebuildStats(&g_Characters[rec]);
            }
            i += 1;
        } while ((u32)(i & BYTE_MASK) < g_Battle.party_count);
    }
    func_801DD08C();
    counter                      = &g_GameEntrySubstate;
    count                        = *counter;
    g_Battle.outcome.event_flags = 0;
    g_Battle.phase.mode          = BATTLE_MODE_ENTRANCE;
    g_Battle.phase.step          = 0;
    g_Battle.phase.sub_step      = 0;
    g_Battle.ui_step             = 0;
    g_Battle.ui_state            = 0;
    *counter                     = count + 1;
}
