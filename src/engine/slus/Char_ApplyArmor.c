#include "engine/slus/slus.h"

/* for each of the shield, helmet and armor ids, adds its table defense and weight to the stat
 * block, then applies the item's own resistance and stat bonuses.
 */
MATCH void Char_ApplyArmor(Character* character) {
    u8     kind_bytes[3];
    u8*    kind;
    Stats* stats;
    u8     i;

    stats         = &character->stats;
    kind_bytes[0] = character->equip.shield;
    kind          = kind_bytes;
    kind_bytes[1] = character->equip.helmet;
    i             = 0;
    kind_bytes[2] = character->equip.armor;
    do {
        Char_AddStat(&stats->defense, g_Armors[*kind].power);
        Char_AddStat(&stats->agility, -g_Armors[*kind].weight);
        switch (*kind) {
            case ARMOR_ASBESTOS_ARMOR:
                Char_AddResistance(&stats->resistances[RES_INDEX_FIRE], 2);
                break;
            case ARMOR_MAGMA_ARMOR:
                Char_AddResistance(&stats->resistances[RES_INDEX_FIRE], 0);
                Char_AddResistance(&stats->resistances[RES_INDEX_FROST], -1);
                break;
            case ARMOR_ROBE_OF_WIND:
                Char_AddResistance(&stats->resistances[RES_INDEX_ELECTRIC], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_EARTH], 4);
                Char_AddResistance(&stats->resistances[RES_INDEX_WIND], 2);
                break;
            case ARMOR_PHANTOM_DRESS:
                Char_AddResistance(&stats->resistances[RES_INDEX_HOLY], -3);
                Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 0);
                Char_AddResistance(&stats->resistances[RES_INDEX_STATUS], 0);
                Char_AddResistance(&stats->resistances[RES_INDEX_PSIONIC], 0);
                break;
            case ARMOR_BLIZZARD_MAIL:
                Char_AddResistance(&stats->resistances[RES_INDEX_FROST], 2);
                break;
            case ARMOR_SAGES_FROCK:
                Char_AddStat(&stats->intellect, 5);
                break;
            case ARMOR_HOLY_ROBE:
            case ARMOR_DIANAS_DRESS:
            case ARMOR_SILVER_TIARA:
                Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_PSIONIC], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_STATUS], 2);
                break;
            case ARMOR_BURGLAR_GARB:
                Char_AddStat(&stats->agility, 5);
                break;
            case ARMOR_FORCE_ARMOR:
                Char_AddResistance(&stats->resistances[RES_INDEX_PSIONIC], 0);
                break;
            case ARMOR_MIST_ARMOR:
                Char_AddResistance(&stats->resistances[RES_INDEX_HOLY], 1);
                Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_PSIONIC], 2);
                Char_AddResistance(&stats->resistances[RES_INDEX_STATUS], 2);
                break;
            case ARMOR_LAUREL:
                Char_AddStat(&stats->unk_0C, 1);
                break;
            case ARMOR_TIGERS_CAP:
                Char_AddStat(&stats->power, 5);
                break;
            case ARMOR_SUN_MASK:
                Char_AddResistance(&stats->resistances[RES_INDEX_FIRE], 2);
                break;
            case ARMOR_DIVINE_HELM:
                Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 0);
                break;
            case ARMOR_FLAME_SHIELD:
                Char_AddResistance(&stats->resistances[RES_INDEX_FIRE], 2);
                break;
            case ARMOR_ICE_SHIELD:
                Char_AddResistance(&stats->resistances[RES_INDEX_FROST], 2);
                break;
            case ARMOR_SPIKED_GAUNTLETS:
                Char_AddStat(&stats->power, 5);
                break;
            case ARMOR_PROTECTORS:
                Char_AddResistance(&stats->resistances[RES_INDEX_STATUS], 2);
                break;
            case ARMOR_MIND_SHIELD:
                Char_AddResistance(&stats->resistances[RES_INDEX_PSIONIC], 2);
                Char_AddStat(&stats->intellect, 5);
                break;
            case ARMOR_DRAGON_ARMOR:
            case ARMOR_DRAGON_HELM:
            case ARMOR_DRAGON_SHIELD:
                Char_AddResistance(&stats->resistances[RES_INDEX_FIRE], 0);
                break;
            case ARMOR_GIDEONS_GARB:
            case ARMOR_ARIES_GLOVES:
                Char_AddStat(&stats->power, 0xA);
                break;
        }
        i++;
        kind++;
    } while (i < 3);
}
