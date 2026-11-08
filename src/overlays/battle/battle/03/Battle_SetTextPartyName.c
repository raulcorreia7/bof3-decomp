#include "battle_03.h"

/* Per-battler selector byte table and ability-template records (stride 0xA4).
 */

MATCH void Battle_SetTextPartyName(u32 party_slot) {
    SYS_CopyString(g_TextVariables[0],
                   (u8*)g_Characters[g_CharSlot[g_Game.members[(party_slot & BYTE_MASK)].chr.character_id]].name, 5u);
}
