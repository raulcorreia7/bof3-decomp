#include "game_00.h"

/* Byte +0x13C of battle local work record 0 (PARTY_COMBATANT_BASE + 0x13C);
 * record i's copy is 0x140 bytes further per index. */

MATCH void func_801BDBC4(void) {
    s32 i;
    s32 offset;
    s32 count;
    u8  found;

    found = 0;
    if (g_GameRequestFlags & 1) {
        i = 0;
        if (i < g_PartySize) {
            count  = g_PartySize;
            offset = 0;
        loop:
            if (g_Characters[D_80145FCC[offset]].status & STATUS_CONFUSED) {
                found = 1;
            }
            i++;
            offset += BATTLE_PARTY_STRIDE;
            if (i < count) {
                /* A structured loop would hoist the table bases. */
                goto loop;
            }
        }
    } else if (g_Characters[g_BattlePartyBattlers[0].character_index].status & STATUS_CONFUSED) {
        found = 1;
    }
    if (found != 0) {
        D_8014625C = (g_InputHeld & INPUT_ACTION_BUTTONS) |
                     (((g_InputHeld & (PADLup | PADLright)) << 2) | ((g_InputHeld & (PADLdown | PADLleft)) >> 2));
    } else {
        D_8014625C = g_InputHeld;
    }
}
