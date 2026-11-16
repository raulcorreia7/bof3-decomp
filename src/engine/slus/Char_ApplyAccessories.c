#include "engine/slus/slus.h"

/* applies the per-kind adjustments for the two equipped accessories:
 * a stat delta from the kind table, then the kind's own counter updates, until two
 * kinds have been handled.
 */
MATCH void Char_ApplyAccessories(Character* character) {
    u8     kinds[2];
    Stats* stats;
    u8*    kind;
    s32    n;
    u16*   pair;
    u8*    counter;
    s32    delta;

    stats    = &character->stats;
    kinds[0] = character->equip.accessories[0];
    kind     = kinds;
    kinds[1] = character->equip.accessories[1];
    n        = 0;
    do {
        Char_AddStat(&stats->agility, -g_OptionItems[*kind].weight);
        switch (*kind) {
            case OPTION_ITEM_TITAN_BELT:
                pair = &stats->power;
                goto block_pair;
            case OPTION_ITEM_HIGH_BOOTS:
                Char_AddStat(&stats->defense, 5);
                break;
            case OPTION_ITEM_SPEED_BOOTS:
                pair = &stats->agility;
            block_pair:
                Char_AddStat(pair, 10);
                break;
            case OPTION_ITEM_WISDOM_RING:
                Char_AddStat(&stats->intelligence, 0x1E);
                break;
            case OPTION_ITEM_LIONS_BELT:
                Char_AddWillpower(&stats->willpower, 10);
                break;
            case OPTION_ITEM_RING_OF_ICE:
                counter = &stats->resistances[RES_INDEX_FROST];
                delta   = 0;
                goto block_counter;
            case OPTION_ITEM_RING_OF_FIRE:
                counter = &stats->resistances[RES_INDEX_FIRE];
                delta   = 0;
                goto block_counter;
            case OPTION_ITEM_THUNDER_RING:
                counter = &stats->resistances[RES_INDEX_ELECTRIC];
                delta   = 0;
                goto block_counter;
            case OPTION_ITEM_TALISMAN:
                counter = &stats->resistances[RES_INDEX_DEATH];
                delta   = 1;
                goto block_counter;
            case OPTION_ITEM_DIAMOND_RING:
                counter = &stats->resistances[RES_INDEX_DEATH];
                delta   = 3;
                goto block_counter;
            case OPTION_ITEM_LIFE_SANDALS:
                counter = &stats->resistances[RES_INDEX_STATUS];
                delta   = 1;
                goto block_counter;
            case OPTION_ITEM_LIGHT_BANGLE:
                counter = &stats->resistances[RES_INDEX_STATUS];
                delta   = 3;
                goto block_counter;
            case OPTION_ITEM_BARRIER_RING:
                counter = &stats->resistances[RES_INDEX_PSIONIC];
                delta   = 3;
                goto block_counter;
            case OPTION_ITEM_HAWKS_RING:
                Char_AddPercent(&stats->surprise_chance, 0x14);
                break;
            case OPTION_ITEM_ARTEMIS_CAP:
                Char_AddPercent(&stats->accuracy, 10);
                break;
            case OPTION_ITEM_IVORY_CHARM:
                Char_AddResistance(&stats->resistances[RES_INDEX_FIRE], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_FROST], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_ELECTRIC], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_EARTH], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_WIND], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_HOLY], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_PSIONIC], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_STATUS], 2);
                counter = &stats->resistances[RES_INDEX_DEATH];
                delta   = 2;
            block_counter:
                Char_AddResistance(counter, delta);
                break;
            default:
                break;
        }
        n++;
        kind++;
    } while ((n & BYTE_MASK) < 2U);
}
