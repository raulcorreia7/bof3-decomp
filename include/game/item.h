#ifndef GAME_ITEM_H
#define GAME_ITEM_H

/* The item, weapon, armor, accessory and vital-item records from `GAME.EMI`,
 * the equipment tables' runtime copies, and the chest, shop and Manillo tables
 * the menu reads. The shop, inventory, equipment and chest code read the
 * runtime copies. Each record type gives the row layout; game/records.h owns
 * the counts and strides.
 *
 * Layout: @source: wiki:data/records#gameemi-fixed-tables. */

#include "types.h"
#include "game/records.h"

#define SHOP_ITEM_REF_SIZE 0x02

/* Item flags: what the menu offers and how the battle selector targets the
 * item. */
typedef enum ItemFlags {
    ITEM_TARGET_BOTH          = 1 << 0,
    ITEM_TARGET_SELECTABLE    = 1 << 1,
    ITEM_TARGET_ENEMY_DEFAULT = 1 << 2,
    ITEM_TARGET_ALL           = 1 << 3,
    ITEM_STORY_ITEM           = 1 << 4,
    ITEM_SHOW_NAME            = 1 << 5,
    ITEM_SHOW_ANIMATION       = 1 << 6,
    ITEM_USABLE_MENU          = 1 << 7,
} ItemFlags;

/* The armor record's equipment slot; NOTHING is the empty armor record. */
typedef enum ArmorType {
    ARMOR_TYPE_NOTHING = 0,
    ARMOR_TYPE_SHIELD  = 2,
    ARMOR_TYPE_HELMET  = 3,
    ARMOR_TYPE_BODY    = 4,
} ArmorType;

/* The kind of a weapon, armor or accessory record (Item_GetKind): it selects the icon the item list draws. Armor
 * records hold their ArmorType; accessory kinds 10 and 11 are the fishing lures and rods, which no equipment slot
 * holds. No record has kind ITEM_TYPE_UNUSED. */
typedef enum ItemType {
    ITEM_TYPE_ITEM         = 0,
    ITEM_TYPE_WEAPON       = 1,
    ITEM_TYPE_SHIELD       = ARMOR_TYPE_SHIELD,
    ITEM_TYPE_HELMET       = ARMOR_TYPE_HELMET,
    ITEM_TYPE_ARMOR        = ARMOR_TYPE_BODY,
    ITEM_TYPE_ACCESSORY    = 5,
    ITEM_TYPE_FISHING_LURE = 10,
    ITEM_TYPE_FISHING_ROD  = 11,
    ITEM_TYPE_UNUSED       = 12,
} ItemType;

/* The equipment slot that holds an item of kind ITEM_TYPE_WEAPON..ITEM_TYPE_ACCESSORY. */
#define EQUIP_SLOT_OF_TYPE(kind) ((kind) - 1)

/* The armor type that fits equipment slot EQUIP_SLOT_SHIELD..EQUIP_SLOT_ARMOR. */
#define ARMOR_TYPE_OF_SLOT(slot) ((slot) + 1)

/* The most of one item an inventory slot holds. */
#define ITEM_STACK_MAX           99

/* The func_801AF494 predicate that holds when bit record_bit of the item's equipability is set. */
#define ITEM_TEST_EQUIPPABLE     4

/* The inventory category code Item_GetRecord resolves a record from. */
typedef enum ItemCategory {
    ITEM_CAT_ITEM      = 0,
    ITEM_CAT_WEAPON    = 1,
    ITEM_CAT_ARMOR     = 2,
    ITEM_CAT_ACCESSORY = 3,
    ITEM_CAT_VITAL     = 4,
    ITEM_CAT_EMPTY     = 0xFF,
} ItemCategory;

typedef struct VitalItem {
    u8  name[ITEM_NAME_LENGTH];
    u16 description; /* Item_GetDescription, category ITEM_CAT_VITAL */
    u16 pad_0E;
} VitalItem;

ASSERT_OFFSET(VitalItem, description, 0x0C);
ASSERT_SIZE(VitalItem, VITAL_ITEM_STRIDE);
ASSERT_OFFSET(VitalItem, name, 0x00);

#define VITAL_ITEM_OBJECT(name, description) {name, (description), 0}

typedef struct Item {
    u8  name[ITEM_NAME_LENGTH];
    u8  flags;       /* ItemFlags */
    u8  icon;        /* low nibble selects the icon */
    u16 description; /* Item_GetDescription, category ITEM_CAT_ITEM */
    u16 price;
} Item;

ASSERT_OFFSET(Item, description, 0x0E);
ASSERT_SIZE(Item, ITEM_STRIDE);
ASSERT_OFFSET(Item, name, 0x00);
ASSERT_OFFSET(Item, flags, 0x0c);
ASSERT_OFFSET(Item, icon, 0x0d);
ASSERT_OFFSET(Item, price, 0x10);

#define ITEM_OBJECT(name, flags, icon, description, price) {name, (flags), (icon), (description), (price)}

/* The run Weapon, Armor and Accessory open with. */
typedef struct ItemHeader {
    u8 name[ITEM_NAME_LENGTH];
    u8 equipability; /* EquipFlags */
    u8 flags;        /* Item_GetFlags; bit tests in func_801AF494 */
} ItemHeader;

ASSERT_SIZE(ItemHeader, 0x0E);

typedef struct Weapon {
    ItemHeader header;
    u8         icon;    /* low nibble selects the icon */
    u8         element; /* ElementFlags */
    u8         weight;
    u8         sound; /* cue-table index in battle/battle/15 func_800AB834 and func_800AB910 */
    u8         power;
    u8         pad_13;
    u16        description; /* Item_GetDescription, category ITEM_CAT_WEAPON */
    u16        price;
} Weapon;

ASSERT_OFFSET(Weapon, description, 0x14);
ASSERT_SIZE(Weapon, WEAPON_STRIDE);
ASSERT_OFFSET(Weapon, header, 0x00);
ASSERT_OFFSET(Weapon, icon, 0x0e);
ASSERT_OFFSET(Weapon, element, 0x0f);
ASSERT_OFFSET(Weapon, weight, 0x10);
ASSERT_OFFSET(Weapon, power, 0x12);
ASSERT_OFFSET(Weapon, price, 0x16);

#define WEAPON_OBJECT(name, equipability, header_flags, icon, element, weight, sound, power, description, price)       \
    {{name, (equipability), (header_flags)}, (icon), (element), (weight), (sound), (power), 0, (description), (price)}

typedef struct Armor {
    ItemHeader header;
    u8         equip_type; /* ArmorType */
    u8         weight;
    u8         power;
    u8         pad_11;
    u16        description; /* Item_GetDescription, category ITEM_CAT_ARMOR */
    u16        price;
} Armor;

ASSERT_OFFSET(Armor, description, 0x12);
ASSERT_SIZE(Armor, ARMOR_STRIDE);
ASSERT_OFFSET(Armor, header, 0x00);
ASSERT_OFFSET(Armor, equip_type, 0x0e);
ASSERT_OFFSET(Armor, weight, 0x0f);
ASSERT_OFFSET(Armor, power, 0x10);
ASSERT_OFFSET(Armor, price, 0x14);

#define ARMOR_OBJECT(name, equipability, header_flags, equip_type, weight, power, description, price)    \
    {{name, (equipability), (header_flags)}, (equip_type), (weight), (power), 0, (description), (price)}

typedef struct Accessory {
    ItemHeader header;
    u8         icon; /* low nibble selects the icon */
    u8         weight;
    u16        description; /* Item_GetDescription, category ITEM_CAT_ACCESSORY */
    u16        price;
} Accessory;

ASSERT_OFFSET(Accessory, description, 0x10);
ASSERT_SIZE(Accessory, ACCESSORY_STRIDE);
ASSERT_OFFSET(Accessory, header, 0x00);
ASSERT_OFFSET(Accessory, icon, 0x0e);
ASSERT_OFFSET(Accessory, weight, 0x0f);
ASSERT_OFFSET(Accessory, price, 0x12);

#define ACCESSORY_OBJECT(name, equipability, header_flags, icon, weight, description, price) {{name, (equipability), (header_flags)}, (icon), (weight), (description), (price)}

/* The g_GameShopStock index a shop counter opens, from the area scripts that spawn it. */
typedef enum ShopId {
    SHOP_MCNEIL_EQUIPMENT               = 0,
    SHOP_MCNEIL_GENERAL                 = 1,
    SHOP_WYNDIA_LOWER_WEAPONS           = 2,
    SHOP_WYNDIA_LOWER_ARMOR             = 3,
    SHOP_WYNDIA_LOWER_ACCESSORIES       = 4,
    SHOP_WYNDIA_LOWER_ITEMS             = 5,
    SHOP_GENMEL_EQUIPMENT               = 6,
    SHOP_GENMEL_ITEMS                   = 7,
    SHOP_MOMO_TOWER_OUTSIDE_GENERAL     = 8,
    SHOP_9                              = 9,
    SHOP_CONTEST_WEAPONS                = 10,
    SHOP_CONTEST_ITEMS                  = 11,
    SHOP_CONTEST_ARMOR                  = 12,
    SHOP_RHAPALA_ENTRANCE_EQUIPMENT     = 13,
    SHOP_RHAPALA_ENTRANCE_GENERAL       = 14,
    SHOP_URKAN_TAPA_EQUIPMENT           = 15,
    SHOP_URKAN_TAPA_GENERAL             = 16,
    SHOP_17                             = 17,
    SHOP_18                             = 18,
    SHOP_19                             = 19,
    SHOP_20                             = 20,
    SHOP_21                             = 21,
    SHOP_22                             = 22,
    SHOP_SYN_CITY_EQUIPMENT             = 23,
    SHOP_SYN_CITY_GENERAL               = 24,
    SHOP_JUNK_TOWN_WEAPONS              = 25,
    SHOP_JUNK_TOWN_GENERAL              = 26,
    SHOP_DAUNA_MINE_ADULT_ITEMS         = 27,
    SHOP_CLIFF_GAIST_GENERAL            = 28,
    SHOP_KOMBINAT_EQUIPMENT             = 29,
    SHOP_KOMBINAT_GENERAL               = 30,
    SHOP_DRAGNIER_SURFACE_ITEMS         = 31,
    SHOP_OASIS_GENERAL                  = 32,
    SHOP_CAER_XHAN_HONEY_ROOM_EQUIPMENT = 33,
    SHOP_34                             = 34,
    SHOP_PARCH_EQUIPMENT                = 35,
    SHOP_PARCH_GENERAL                  = 36,
    SHOP_RHAPALA_CHECKPOINT_ITEMS       = 37,
    SHOP_WYNDIA_UPPER_ITEMS             = 38,
    SHOP_SYN_CITY_EQUIPMENT_2           = 39,
} ShopId;

typedef struct ShopItemRef {
    u8 item_type; /* ItemCategory */
    u8 item_index;
} ShopItemRef;

typedef struct ShopStock {
    u8          item_count;
    ShopItemRef slots[SHOP_STOCK_MAX];
} ShopStock;

ASSERT_SIZE(ShopItemRef, SHOP_ITEM_REF_SIZE);
ASSERT_SIZE(ShopStock, SHOP_STRIDE);

#define SHOP_ITEM(item_type, item_index) {(item_type), (item_index)}

#define SHOP_OBJECT(item_count, slot0, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
    {                                                                                                         \
        (item_count), {                                                                                       \
            slot0, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10                      \
        }                                                                                                     \
    }

typedef struct Chest {
    u8 memory;
    u8 item_index;
    u8 item_type;
} Chest;

ASSERT_SIZE(Chest, CHEST_STRIDE);

typedef struct ManilloTrade {
    u8 item_index;
    u8 item_type;
    u8 fish_indexes[MANILLO_FISH_COUNT];
    u8 fish_quantities[MANILLO_FISH_COUNT];
} ManilloTrade;

ASSERT_SIZE(ManilloTrade, MANILLO_ITEM_STRIDE);

typedef struct ManilloStock {
    u8 trade_indexes[MANILLO_TRADE_COUNT];
} ManilloStock;

ASSERT_SIZE(ManilloStock, MANILLO_STOCK_STRIDE);

/* The item table ids (category ITEM_CAT_ITEM). Names from the GAME.EMI record tables. */
typedef enum ItemId {
    ITEM_NOTHING       = 0,
    ITEM_GREEN_APPLE   = 1,
    ITEM_BREAD         = 2,
    ITEM_HEALING_HERB  = 3,
    ITEM_VITAMIN       = 4,
    ITEM_MULTIVITAMIN  = 5,
    ITEM_VITAMINS      = 6,
    ITEM_WISDOM_SEED   = 7,
    ITEM_WISDOM_FRUIT  = 8,
    ITEM_CROC_TEAR     = 9,
    ITEM_ANTIDOTE      = 10,
    ITEM_EYE_DROPS     = 11,
    ITEM_THE_MOCHI     = 12,
    ITEM_PANACEA       = 13,
    ITEM_AMMONIA       = 14,
    ITEM_MOON_TEARS    = 15,
    ITEM_DYNAMITE      = 16,
    ITEM_WEATHER_VANE  = 17,
    ITEM_TASER         = 18,
    ITEM_BELLADONNA    = 19,
    ITEM_GINSENG       = 20,
    ITEM_FIRECRACKER   = 21,
    ITEM_ICICLE        = 22,
    ITEM_NAPALM        = 23,
    ITEM_MOLOTOV       = 24,
    ITEM_LIFE_SHARD    = 25,
    ITEM_MAGIC_SHARD   = 26,
    ITEM_POWER_FOOD    = 27,
    ITEM_PROTEIN       = 28,
    ITEM_SWALLOW_EYE   = 29,
    ITEM_FISH_HEAD     = 30,
    ITEM_MOXA          = 31,
    ITEM_HOURGLASS     = 32,
    ITEM_IVORY_DICE    = 33,
    ITEM_PLATE         = 34,
    ITEM_SHALY_SEED    = 35,
    ITEM_VINEGAR       = 36,
    ITEM_RUSTED_MEDAL  = 37,
    ITEM_GEMS          = 38,
    ITEM_BEEF_JERKY    = 39,
    ITEM_CHEESE        = 40,
    ITEM_BERRIES       = 41,
    ITEM_MANDRAKE      = 42,
    ITEM_CLAY_VASE     = 43,
    ITEM_MARBLES       = 44,
    ITEM_MOLDY_VASE    = 45,
    ITEM_DIRTY_RAGS    = 46,
    ITEM_TEA_CUP       = 47,
    ITEM_BEADS         = 48,
    ITEM_RARE_BOOK     = 49,
    ITEM_OLD_PAINTING  = 50,
    ITEM_MYRIA_ICON    = 51,
    ITEM_LADON_ICON    = 52,
    ITEM_LITHOGRAPH    = 53,
    ITEM_DRAGON_TEAR   = 54,
    ITEM_RICE_BALL     = 55,
    ITEM_JELLYFISH     = 56,
    ITEM_PIRANA        = 57,
    ITEM_PUFFER        = 58,
    ITEM_TROUT         = 59,
    ITEM_RAINBOW_TROUT = 60,
    ITEM_RED_CATFISH   = 61,
    ITEM_BASS          = 62,
    ITEM_MARTIAN_SQUID = 63,
    ITEM_BLACK_BASS    = 64,
    ITEM_BARANDY       = 65,
    ITEM_MAN_O         = 66,
    ITEM_FLYING_FISH   = 67,
    ITEM_BLOWFISH      = 68,
    ITEM_SEA_BREAM     = 69,
    ITEM_SEA_BASS      = 70,
    ITEM_BLACK_PORGY   = 71,
    ITEM_OCTOPUS       = 72,
    ITEM_ANGLER        = 73,
    ITEM_DEVILFISH     = 74,
    ITEM_SPEARFISH     = 75,
    ITEM_WHALE         = 76,
    ITEM_MACKEREL      = 77,
    ITEM_PART_A        = 78,
    ITEM_PART_B        = 79,
    ITEM_PART_C        = 80,
    ITEM_PART_D        = 81,
    ITEM_PART_E        = 82,
    ITEM_PART_F        = 83,
    ITEM_PART_G        = 84,
    ITEM_PART_H        = 85,
    ITEM_HORSERADISH   = 86,
    ITEM_FAERIE_TIARA  = 87,
    ITEM_SKILL_INK     = 88,
    ITEM_FLOWER_JEWEL  = 89,
    ITEM_RAKDA_MEAT    = 90,
    ITEM_WATER_JUG     = 91,
} ItemId;

/* The weapon table ids (category ITEM_CAT_WEAPON). Names from the GAME.EMI record tables. */
typedef enum WeaponId {
    WEAPON_NOTHING        = 0,
    WEAPON_DAGGER         = 1,
    WEAPON_BALLOCK_KNIFE  = 2,
    WEAPON_BRONZE_SWORD   = 3,
    WEAPON_BROAD_SWORD    = 4,
    WEAPON_SILVER_KNIFE   = 5,
    WEAPON_SCRAMASAX      = 6,
    WEAPON_MOON_SWORD     = 7,
    WEAPON_CLAYMORE       = 8,
    WEAPON_FLARE_SWORD    = 9,
    WEAPON_FEATHER_SWORD  = 10,
    WEAPON_ROYAL_DAGGER   = 11,
    WEAPON_BASELARD       = 12,
    WEAPON_DEADLY_BLADE   = 13,
    WEAPON_HEAVY_DAGGER   = 14,
    WEAPON_ASCENSION      = 15,
    WEAPON_HEAT_SHOTEL    = 16,
    WEAPON_BARBAROSSA     = 17,
    WEAPON_PIERCING_EDGE  = 18,
    WEAPON_DEMONSBANE     = 19,
    WEAPON_DAMASCUS_SWORD = 20,
    WEAPON_SEEKING_SWORD  = 21,
    WEAPON_DRAGON_BLADE   = 22,
    WEAPON_HOLY_AVENGER   = 23,
    WEAPON_ROYAL_SWORD    = 24,
    WEAPON_GOO_KING_SWORD = 25,
    WEAPON_ASHURAS_SWORD  = 26,
    WEAPON_HIDDEN_DAGGER  = 27,
    WEAPON_BENT_SWORD     = 28,
    WEAPON_POINTED_STICK  = 29,
    WEAPON_OAKEN_STAFF    = 30,
    WEAPON_MACE           = 31,
    WEAPON_MAGICIAN_ROD   = 32,
    WEAPON_QUARTER_STAFF  = 33,
    WEAPON_WIND_CUTTER    = 34,
    WEAPON_RUBY_SCEPTER   = 35,
    WEAPON_LACQUER_STAFF  = 36,
    WEAPON_BERYL_ROD      = 37,
    WEAPON_THUNDER_ROD    = 38,
    WEAPON_BLESSED_STAFF  = 39,
    WEAPON_OUROBOROS      = 40,
    WEAPON_SPEAR          = 41,
    WEAPON_LONG_SPEAR     = 42,
    WEAPON_HALBERD        = 43,
    WEAPON_ROOD_SPEAR     = 44,
    WEAPON_FLAME_SPEAR    = 45,
    WEAPON_FLYING_SPEAR   = 46,
    WEAPON_PIERCING_PIKE  = 47,
    WEAPON_GIGANTESS      = 48,
    WEAPON_GALE_JAVELIN   = 49,
    WEAPON_ICE_HALBERD    = 50,
    WEAPON_ARIES_SPEAR    = 51,
    WEAPON_GUNGINIR       = 52,
    WEAPON_DRAGON_SPEAR   = 53,
    WEAPON_RUFADS_SPEAR   = 54,
    WEAPON_CLAWS          = 55,
    WEAPON_RIPPERS        = 56,
    WEAPON_SPIKED_CLAWS   = 57,
    WEAPON_FLAME_TALONS   = 58,
    WEAPON_TIGER_CLAWS    = 59,
    WEAPON_RAPTOR_CLAWS   = 60,
    WEAPON_ROCKBREAKER    = 61,
    WEAPON_BRASS_CLAWS    = 62,
    WEAPON_DEATH_CLAWS    = 63,
    WEAPON_DRAGONFANG     = 64,
    WEAPON_THIEVES_KNIFE  = 65,
    WEAPON_KATZBALGER     = 66,
    WEAPON_SLICER         = 67,
    WEAPON_LIFESTEALER    = 68,
    WEAPON_MELTED_BLADE   = 69,
    WEAPON_AMMO           = 70,
    WEAPON_FLAME_CHRYSM   = 71,
    WEAPON_ICE_CHRYSM     = 72,
    WEAPON_SHOTGUN_SHELL  = 73,
    WEAPON_SLEEP_SHELLS   = 74,
    WEAPON_HE_SHELLS      = 75,
    WEAPON_FLASH_SHELLS   = 76,
    WEAPON_HOMING_BOMB    = 77,
    WEAPON_AP_SHELLS      = 78,
    WEAPON_GAS_SHELLS     = 79,
    WEAPON_ATOMIC_BOMB    = 80,
    WEAPON_GHOSTBUSTER    = 81,
    WEAPON_BEAST_SPEAR    = 82,
} WeaponId;

/* The armor table ids (category ITEM_CAT_ARMOR). Names from the GAME.EMI record tables. */
typedef enum ArmorId {
    ARMOR_NOTHING           = 0,
    ARMOR_CLOTHING          = 1,
    ARMOR_LEATHER_ARMOR     = 2,
    ARMOR_WAISTCLOTH        = 3,
    ARMOR_RANGER_GARB       = 4,
    ARMOR_LEATHER_APRON     = 5,
    ARMOR_MAGES_ROBES       = 6,
    ARMOR_CUIRASS           = 7,
    ARMOR_BREASTPLATE       = 8,
    ARMOR_CHAIN_CAP         = 9,
    ARMOR_SCALE_MAIL        = 10,
    ARMOR_CREPE_CAPE        = 11,
    ARMOR_ASBESTOS_ARMOR    = 12,
    ARMOR_MITHRIL_ARMOR     = 13,
    ARMOR_LIGHT_CLOTHING    = 14,
    ARMOR_MAGMA_ARMOR       = 15,
    ARMOR_SILVER_MAIL       = 16,
    ARMOR_ROBE_OF_WIND      = 17,
    ARMOR_AMBER_BREASTPLATE = 18,
    ARMOR_PHANTOM_DRESS     = 19,
    ARMOR_BLIZZARD_MAIL     = 20,
    ARMOR_LACQUER_ARMOR     = 21,
    ARMOR_SAGES_FROCK       = 22,
    ARMOR_DAMASCUS_MAIL     = 23,
    ARMOR_HOLY_ROBE         = 24,
    ARMOR_BURGLAR_GARB      = 25,
    ARMOR_ROYAL_ARMOR       = 26,
    ARMOR_FORCE_ARMOR       = 27,
    ARMOR_GIDEONS_GARB      = 28,
    ARMOR_DIANAS_DRESS      = 29,
    ARMOR_DRAGON_ARMOR      = 30,
    ARMOR_LIFE_ARMOR        = 31,
    ARMOR_MIST_ARMOR        = 32,
    ARMOR_BANDANA           = 33,
    ARMOR_HAIRBAND          = 34,
    ARMOR_BRASS_HELM        = 35,
    ARMOR_IRON_HELM         = 36,
    ARMOR_KNIGHTS_HELM      = 37,
    ARMOR_GLASS_DOMINO      = 38,
    ARMOR_MITHRIL_HELM      = 39,
    ARMOR_LAUREL            = 40,
    ARMOR_GOLD_HAIRPIN      = 41,
    ARMOR_PLATINUM_HELM     = 42,
    ARMOR_UV_GLASSES        = 43,
    ARMOR_TIGERS_CAP        = 44,
    ARMOR_SUN_MASK          = 45,
    ARMOR_LACQUER_HELM      = 46,
    ARMOR_SILVER_TIARA      = 47,
    ARMOR_DIVINE_HELM       = 48,
    ARMOR_DRAGON_HELM       = 49,
    ARMOR_BRACERS           = 50,
    ARMOR_CLOTH_SHIELD      = 51,
    ARMOR_GAUNTLET          = 52,
    ARMOR_BRONZE_SHIELD     = 53,
    ARMOR_BUCKLER           = 54,
    ARMOR_MITHRIL_SHIELD    = 55,
    ARMOR_STEEL_GAUNTLETS   = 56,
    ARMOR_FLAME_SHIELD      = 57,
    ARMOR_KITE_SHIELD       = 58,
    ARMOR_ICE_SHIELD        = 59,
    ARMOR_SPIKED_GAUNTLETS  = 60,
    ARMOR_LACQUER_SHIELD    = 61,
    ARMOR_PROTECTORS        = 62,
    ARMOR_GIANT_SHIELD      = 63,
    ARMOR_MIND_SHIELD       = 64,
    ARMOR_DRAGON_SHIELD     = 65,
    ARMOR_ARIES_GLOVES      = 66,
    ARMOR_MANLY_CLOTHES     = 67,
} ArmorId;

/* The accessory table ids (category ITEM_CAT_ACCESSORY). Names from the GAME.EMI record tables. */
typedef enum AccessoryId {
    ACCESSORY_NOTHING      = 0,
    ACCESSORY_TITAN_BELT   = 1,
    ACCESSORY_HIGH_BOOTS   = 2,
    ACCESSORY_SPEED_BOOTS  = 3,
    ACCESSORY_WISDOM_RING  = 4,
    ACCESSORY_LIONS_BELT   = 5,
    ACCESSORY_DREAM_RING   = 6,
    ACCESSORY_MIDAS_STONE  = 7,
    ACCESSORY_BALANCE_RING = 8,
    ACCESSORY_BAT_AMULET   = 9,
    ACCESSORY_RING_OF_ICE  = 10,
    ACCESSORY_RING_OF_FIRE = 11,
    ACCESSORY_THUNDER_RING = 12,
    ACCESSORY_TALISMAN     = 13,
    ACCESSORY_DIAMOND_RING = 14,
    ACCESSORY_LIFE_SANDALS = 15,
    ACCESSORY_LIGHT_BANGLE = 16,
    ACCESSORY_BARRIER_RING = 17,
    ACCESSORY_HAWKS_RING   = 18,
    ACCESSORY_ARTEMIS_CAP  = 19,
    ACCESSORY_BELL_COLLAR  = 20,
    ACCESSORY_HOLY_MANTLE  = 21,
    ACCESSORY_CUPIDS_LYRE  = 22,
    ACCESSORY_IVORY_CHARM  = 23,
    ACCESSORY_SOUL_GEM     = 24,
    ACCESSORY_SHAMANS_RING = 25,
    ACCESSORY_SPIRIT_RING  = 26,
    ACCESSORY_COUPONS      = 27,
    ACCESSORY_WORM         = 28,
    ACCESSORY_SPIRIT       = 29,
    ACCESSORY_CARO         = 30,
    ACCESSORY_HEAVY_CARO   = 31,
    ACCESSORY_TOAD         = 32,
    ACCESSORY_BABY_FROG    = 33,
    ACCESSORY_FROG         = 34,
    ACCESSORY_FAT_FROG     = 35,
    ACCESSORY_OLD_POPPER   = 36,
    ACCESSORY_POPPER       = 37,
    ACCESSORY_TOP          = 38,
    ACCESSORY_DOGWALKER    = 39,
    ACCESSORY_SINKER       = 40,
    ACCESSORY_FLOAT        = 41,
    ACCESSORY_HANGER       = 42,
    ACCESSORY_DEEP_DIVER   = 43,
    ACCESSORY_COIN         = 44,
    ACCESSORY_DING_FROG    = 45,
    ACCESSORY_WOODEN_ROD   = 46,
    ACCESSORY_BAMBOO_ROD   = 47,
    ACCESSORY_DELUXE_ROD   = 48,
    ACCESSORY_ANGLING_ROD  = 49,
    ACCESSORY_SPANNER      = 50,
    ACCESSORY_MASTERS_ROD  = 51,
} AccessoryId;

/* The vital item table ids (category ITEM_CAT_VITAL). Names from the GAME.EMI record tables. */
typedef enum VitalItemId {
    VITAL_ITEM_FLIER        = 1,
    VITAL_ITEM_WALLET       = 2,
    VITAL_ITEM_EGG          = 3,
    VITAL_ITEM_PASSPORT     = 4,
    VITAL_ITEM_GUILD_LETTER = 5,
    VITAL_ITEM_ID_CARD      = 6,
    VITAL_ITEM_GUILD_BADGE  = 7,
    VITAL_ITEM_SYSTEM_DISK  = 8,
    VITAL_ITEM_MEMO         = 9,
    VITAL_ITEM_SEA_CHARTS   = 10,
    VITAL_ITEM_KEY          = 11,
    VITAL_ITEM_CARD_KEY_A   = 12,
    VITAL_ITEM_CARD_KEY_B   = 13,
    VITAL_ITEM_OLD_PASSPORT = 14,
    VITAL_ITEM_FOUNTAIN_PEN = 15,
} VitalItemId;

/* The five equipment tables; counts are owned by game/records.h. Read through
 * the record types above so the offsets stay declared in one place. */
/* D_801C8964 */
extern volatile Item      g_Items[];
/* The two cells the retail materializes by symbol in each equipment table: the
 * row's flags byte and its price halfword. The record types above hold them at
 * their offsets, but a reader that walks a table by the cell's own symbol
 * needs the cell named; the row's stride is the record's stride.
 *
 * The offsets are Item.flags and .price, Weapon.flags and .price,
 * Armor.flags and .price, and Accessory.flags and .price. */
extern u8                 D_801C8970[]; /* the item row's flags byte */
extern u8                 D_801C8974;   /* the item row's price halfword */
/* D_801C8FDC */
extern volatile VitalItem g_VitalItems[];
/* D_801C90DC */
extern Weapon             g_Weapons[];
extern u8                 D_801C90E9[]; /* the weapon row's flags byte */
extern u8                 D_801C90F2;   /* the weapon row's price halfword */
/* D_801C98A4 */
extern Armor              g_Armors[];
extern u8                 D_801C98B1[]; /* the armor row's flags byte */
extern u8                 D_801C98B8;   /* the armor row's price halfword */
/* D_801C9E7C */
extern volatile Accessory g_Accessories[];
extern u8                 D_801C9E89[]; /* the accessory row's flags byte */
extern u8                 D_801C9E8E;   /* the accessory row's price halfword */

/* Resolves one GAME.EMI equipment record from its category and key: the
 * category selects the item, weapon, armor, accessory or vital-item table above,
 * the key the record inside it. Retail unit exe/slus_004_22@0x80165D48. */

#endif
