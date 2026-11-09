#include "battle_15.h"

/* picks the dragon form row whose three gene slots are all free:
 * func_800A6CF8 reports a slot as free while its gene is the 0xFF wildcard or
 * already one of the party's, and the first row that passes every slot copies
 * D_800B4D4C's companion gene into BATTLE_DRAGON_COMPANION and returns the row.
 * Row 6 asks func_800A6D84 for the battle formation first and returns its
 * pick when it has one; 0xFF means no row qualified.
 */
MATCH u8 func_800A6C2C(void) {
    u8 row;
    u8 slot;
    u8 pick;

    for (row = 0; row < COMBATANT_COUNT; row++) {
        if (row == 6) {
            pick = func_800A6D84() & BYTE_MASK;
            if (pick != 0) {
                return pick;
            }
            row++;
        }
        for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
            if ((func_800A6CF8(row, slot) & BYTE_MASK) == 0) {
                break;
            }
        }
        if (slot == 3) {
            D_800B6F5C = D_800B4D4C[row];
            return row;
        }
    }
    return 0xFF;
}
