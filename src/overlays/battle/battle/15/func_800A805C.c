#include "battle_15.h"

u8 func_800A82A0(u8 selection_id); /* extern */

/* picks the battle formation: collects the flag byte of each live,
 * non-active party slot, then accepts one of the six directional pairs,
 * retrying once with the pair swapped.
 */
MATCH u8 func_800A805C(void) {
    u8 slots[PARTY_SLOT_COUNT];
    u8 count; /* collected flag count; the swap below reuses its storage */
    u8 slot;
    u8 tries;

    count = 0;
    slot  = 0;
    do {
        if (LOBU(g_BattleActiveBattler) != slot) {
            if (Battle_SlotIsBlocked(slot) == 0) {
                slots[count] = g_Game.members[slot].chr.character_id;
                count++;
            }
        }
        slot++;
    } while (slot < PARTY_SLOT_COUNT);

    tries = 0;
    for (;;) {
        switch (slots[0]) {
            case 1:
            case 8:
                if (slots[1] == 2 || slots[1] == 6) {
                    if (func_800A82A0(7) != 0) {
                        D_800B6F5C = 1;
                        return 0xC;
                    }
                    return 0xB;
                }
                break;
            case 2:
                if ((u8)(slots[1] - 4) < 2) {
                    return 0;
                }
                break;
            case 4:
                if (slots[1] == 5 || slots[1] == 8 || slots[1] == 1) {
                    if (func_800A82A0(5) != 0) {
                        D_800B6F5C = 1;
                        return 0x12;
                    }
                    return 0x11;
                }
                break;
            case 5:
                if (slots[1] == 8 || slots[1] == 1 || slots[1] == 6) {
                    if (func_800A82A0(0xD) != 0) {
                        D_800B6F5C = 1;
                        return 0x14;
                    }
                    return 0x13;
                }
                break;
            case 6:
                if (slots[1] == 2 || slots[1] == 4) {
                    if (func_800A82A0(3) != 0) {
                        D_800B6F5C = 1;
                        return 0xE;
                    }
                    return 0xD;
                }
                break;
        }
        /* Rotate the two collected flag bytes; the counter's storage carries
         * the saved first byte, as the original keeps it in that register. */
        count    = slots[0];
        slots[0] = slots[1];
        slots[1] = count;
        tries++;
        if (tries >= 2) {
            return 0xFF;
        }
    }
}
