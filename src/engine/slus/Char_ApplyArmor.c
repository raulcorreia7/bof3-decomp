#include "engine/slus/slus.h"

/* for the three kind bytes at +0x0F..+0x11, sets the 16-bit fields at record +6 and +8 from the
 * 0x16-stride table at D_801C98B4/D_801C98B3, then nudges the kind's 16-bit and byte counters in the +0x1C record body.
 */
MATCH void Char_ApplyArmor(void* character) {
    u8  kind_bytes[3];
    u8* kind;
    u8* record;
    u8  i;

    record        = (u8*)character + 0x1C;
    kind_bytes[0] = ((u8*)character)[0xF];
    kind          = kind_bytes;
    kind_bytes[1] = ((u8*)character)[0x10];
    i             = 0;
    kind_bytes[2] = ((u8*)character)[0x11];
    do {
        Char_AddStat((u16*)(record + 6), D_801C98B4[*kind * 0x16]);
        Char_AddStat((u16*)(record + 8), -D_801C98B3[*kind * 0x16]);
        switch (*kind) {
            case ARMOR_ASBESTOS_ARMOR:
                Char_AddResistance(record + 0xF, 2);
                break;
            case ARMOR_MAGMA_ARMOR:
                Char_AddResistance(record + 0xF, 0);
                Char_AddResistance(record + 0x10, -1);
                break;
            case ARMOR_ROBE_OF_WIND:
                Char_AddResistance(record + 0x11, 2);
                Char_AddResistance(record + 0x12, 4);
                Char_AddResistance(record + 0x13, 2);
                break;
            case ARMOR_PHANTOM_DRESS:
                Char_AddResistance(record + 0x14, -3);
                Char_AddResistance(record + 0x17, 0);
                Char_AddResistance(record + 0x16, 0);
                Char_AddResistance(record + 0x15, 0);
                break;
            case ARMOR_BLIZZARD_MAIL:
                Char_AddResistance(record + 0x10, 2);
                break;
            case ARMOR_SAGES_FROCK:
                Char_AddStat((u16*)(record + 0xA), 5);
                break;
            case ARMOR_HOLY_ROBE:
            case ARMOR_DIANAS_DRESS:
            case ARMOR_SILVER_TIARA:
                Char_AddResistance(record + 0x17, 2);
                Char_AddResistance(record + 0x15, 2);
                Char_AddResistance(record + 0x16, 2);
                break;
            case ARMOR_BURGLAR_GARB:
                Char_AddStat((u16*)(record + 8), 5);
                break;
            case ARMOR_FORCE_ARMOR:
                Char_AddResistance(record + 0x15, 0);
                break;
            case ARMOR_MIST_ARMOR:
                Char_AddResistance(record + 0x14, 1);
                Char_AddResistance(record + 0x17, 2);
                Char_AddResistance(record + 0x15, 2);
                Char_AddResistance(record + 0x16, 2);
                break;
            case ARMOR_LAUREL:
                Char_AddStat((u16*)(record + 0xC), 1);
                break;
            case ARMOR_TIGERS_CAP:
                Char_AddStat((u16*)(record + 4), 5);
                break;
            case ARMOR_SUN_MASK:
                Char_AddResistance(record + 0xF, 2);
                break;
            case ARMOR_DIVINE_HELM:
                Char_AddResistance(record + 0x17, 0);
                break;
            case ARMOR_FLAME_SHIELD:
                Char_AddResistance(record + 0xF, 2);
                break;
            case ARMOR_ICE_SHIELD:
                Char_AddResistance(record + 0x10, 2);
                break;
            case ARMOR_SPIKED_GAUNTLETS:
                Char_AddStat((u16*)(record + 4), 5);
                break;
            case ARMOR_PROTECTORS:
                Char_AddResistance(record + 0x16, 2);
                break;
            case ARMOR_MIND_SHIELD:
                Char_AddResistance(record + 0x15, 2);
                Char_AddStat((u16*)(record + 0xA), 5);
                break;
            case ARMOR_DRAGON_ARMOR:
            case ARMOR_DRAGON_HELM:
            case ARMOR_DRAGON_SHIELD:
                Char_AddResistance(record + 0xF, 0);
                break;
            case ARMOR_GIDEONS_GARB:
            case ARMOR_ARIES_GLOVES:
                Char_AddStat((u16*)(record + 4), 0xA);
                break;
        }
        i++;
        kind++;
    } while (i < 3);
}
