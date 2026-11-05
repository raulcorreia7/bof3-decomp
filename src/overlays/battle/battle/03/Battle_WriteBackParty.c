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
    if (g_BattlePartyCount != 0) {
        do {
            index = i & BYTE_MASK;
            off   = index * BATTLE_PARTY_STRIDE;
            if ((*(u16*)((D_80145F10 + off)) & 0x4000u) != 0u) {
                rec                                 = D_80145FCC[off];
                value                               = g_Characters[rec].fatigue;
                g_Characters[rec].current_hp        = 1;
                g_Characters[rec].current_willpower = 1;
                if (value < 5u) {
                    g_Characters[rec].fatigue = value + 1;
                }
                g_Characters[rec].status &= ~STATUS_KO;
                g_Characters[rec].unk_07 &= 0xFBu;
                Char_RebuildStats(&g_Characters[rec]);
            }
            i += 1;
        } while ((u32)(i & BYTE_MASK) < g_BattlePartyCount);
    }
    func_801DD08C();
    counter            = &g_GameEntrySubstate;
    count              = *counter;
    g_BattleEventFlags = 0;
    g_BattleMode       = 0;
    g_BattleStep       = 0;
    g_BattleSubStep    = 0;
    g_BattleUiStep     = 0;
    g_BattleUiState    = 0;
    *counter           = count + 1;
}
