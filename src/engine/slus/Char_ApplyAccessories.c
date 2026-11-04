#include "engine/slus/slus.h"

/* applies the per-kind adjustments for the two kind bytes at 0x12 and 0x13:
 * a stat delta from the kind table, then the kind's own counter updates, until two
 * kinds have been handled.
 */
MATCH void Char_ApplyAccessories(void* param) {
    u8*  base = param;
    u8   kinds[2];
    u8*  p;
    u8*  kind;
    s32  n;
    u16* pair;
    u8*  counter;
    s32  delta;

    p        = base + 0x1C;
    kinds[0] = base[0x12];
    kind     = kinds;
    kinds[1] = base[0x13];
    n        = 0;
    do {
        Char_AddStat((u16*)(p + 8), -D_801C9E8B[*kind * 0x14]);
        switch (*kind) {
            case ACCESSORY_TITAN_BELT:
                pair = (u16*)(p + 4);
                /* retail shares the call tail with case 3. */
                goto block_pair;
            case ACCESSORY_HIGH_BOOTS:
                Char_AddStat((u16*)(p + 6), 5);
                break;
            case ACCESSORY_SPEED_BOOTS:
                pair = (u16*)(p + 8);
            block_pair:
                Char_AddStat(pair, 10);
                break;
            case ACCESSORY_WISDOM_RING:
                Char_AddStat((u16*)(p + 0xA), 0x1E);
                break;
            case ACCESSORY_LIONS_BELT:
                Char_AddWillpower(p + 0xE, 10);
                break;
            case ACCESSORY_RING_OF_ICE:
                counter = p + 0x10;
                delta   = 0;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_RING_OF_FIRE:
                counter = p + 0xF;
                delta   = 0;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_THUNDER_RING:
                counter = p + 0x11;
                delta   = 0;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_TALISMAN:
                counter = p + 0x17;
                delta   = 1;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_DIAMOND_RING:
                counter = p + 0x17;
                delta   = 3;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_LIFE_SANDALS:
                counter = p + 0x16;
                delta   = 1;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_LIGHT_BANGLE:
                counter = p + 0x16;
                delta   = 3;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_BARRIER_RING:
                counter = p + 0x15;
                delta   = 3;
                /* retail shares one counter call after case 23. */
                goto block_counter;
            case ACCESSORY_HAWK_S_RING:
                Char_AddPercent(p + 0x18, 0x14);
                break;
            case ACCESSORY_ARTEMIS_CAP:
                Char_AddPercent(p + 0x1C, 10);
                break;
            case ACCESSORY_IVORY_CHARM:
                Char_AddResistance(p + 0xF, 2);
                Char_AddResistance(p + 0x10, 2);
                Char_AddResistance(p + 0x11, 2);
                Char_AddResistance(p + 0x12, 2);
                Char_AddResistance(p + 0x13, 2);
                Char_AddResistance(p + 0x14, 2);
                Char_AddResistance(p + 0x15, 2);
                Char_AddResistance(p + 0x16, 2);
                counter = p + 0x17;
                delta   = 2;
            block_counter:
                Char_AddResistance(counter, delta);
                break;
            default:
                break;
        }
        n++;
        kind++;
    } while ((u32)(n & BYTE_MASK) < 2U);
}
