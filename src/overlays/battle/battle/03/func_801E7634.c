#include "battle_03.h"

/* Action values, one u16 per 0x140-byte battler row. */

/* installs the active battler's local work record as the scratchpad work record, refreshes the battle
 * tables and cursors for its slot, clears the record's low flag, then restores the previous record and advances its
 * counter.
 */
MATCH void func_801E7634(void) {
    PartyMember* saved;

    if (EMI_IsReady() != 0) {
        saved = SELF(PartyMember);
        SELF_SET(g_BattleEffectBattler);
        g_GameState = &g_Game.members[g_BattleEffectBattler->slot];
        Script_Select((g_BattleEffectBattler->facing + 4) & BYTE_MASK);
        GFX_PaletteFreeFadeTarget(&g_Game.members[SELF(PartyMember)->slot]);
        GFX_PaletteLoad((SELF(PartyMember)->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, 0);
        func_801DDAB4(g_Game.members[SELF(PartyMember)->slot].chr.status);
        GFX_PaletteUploadRows();
        g_Game.current->u.turn.action_flags.value &= ~BATTLER_ACTION_DRAGON_FORM_QUEUED;
        func_801E0B64();
        SELF_SET(saved);
        saved->header.mode++;
    }
}
