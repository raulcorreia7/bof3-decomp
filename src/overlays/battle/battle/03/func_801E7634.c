#include "battle_03.h"

/* Action values, one u16 per 0x140-byte battler row. */

/* installs the active battler's local work record as the scratchpad work record, refreshes the battle
 * tables and cursors for its slot, clears the record's low flag, then restores the previous record and advances its
 * counter.
 */
MATCH void func_801E7634(void) {
    PartyBattler* saved;

    if (EMI_LoaderIsReady() != 0) {
        saved       = g_SpadWork;
        g_SpadWork  = D_801EB4E0;
        g_GameState = &g_BattlePartyBattlers[D_801EB4E0->slot];
        Actor_SelectScript((D_801EB4E0->word_08.byte.unk_08 + 4) & BYTE_MASK);
        GFX_FreePaletteFadeTarget(&g_BattlePartyBattlers[g_SpadWork->slot]);
        GFX_StagePalette((g_SpadWork->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, 0);
        func_801DDAB4(g_BattlePartyBattlers[g_SpadWork->slot].stats.status);
        GFX_UploadPaletteRows();
        g_GameState->flags_128.value &= ~1;
        func_801E0B64();
        g_SpadWork = saved;
        saved->step_01++;
    }
}
