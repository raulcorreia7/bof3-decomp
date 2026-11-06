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

#define SHOP_ITEM_REF_SIZE                           0x02

/* Static record constructors, in field order. */
#define SHOP_ITEM_REF(item_type, item_index)         {(item_type), (item_index)}

/* Zero bytes are fixed shipped values, not constructor parameters.
 * Resource IDs are read as u16 by Item_GetDescription. */
#define ITEM_OBJECT(name, flags, description, price) {name, (flags), 0, (description), (price)}
#define VITAL_ITEM_OBJECT(name, description)         {name, (description), 0}
#define WEAPON_OBJECT(name, equipability, flags, kind, element, weight, sound, power, description, price)     \
    {name, (equipability), (flags), (kind), (element), (weight), (sound), (power), 0, (description), (price)}
#define ARMOR_OBJECT(name, equipability, flags, equip_type, weight, power, description, price)  \
    {name, (equipability), (flags), (equip_type), (weight), (power), 0, (description), (price)}
#define ACCESSORY_OBJECT(name, equipability, flags, kind, weight, description, price) \
    {name, (equipability), (flags), (kind), (weight), (description), (price)}

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
    u16 unk_0E;
} VitalItem;

ASSERT_OFFSET(VitalItem, description, 0x0C);
ASSERT_SIZE(VitalItem, VITAL_ITEM_STRIDE);
ASSERT_OFFSET(VitalItem, name, 0x00);

typedef struct Item {
    u8  name[ITEM_NAME_LENGTH];
    u8  flags; /* ItemFlags */
    u8  unk_0D;
    u16 description; /* Item_GetDescription, category ITEM_CAT_ITEM */
    u16 price;
} Item;

ASSERT_OFFSET(Item, description, 0x0E);
ASSERT_SIZE(Item, ITEM_STRIDE);
ASSERT_OFFSET(Item, name, 0x00);
ASSERT_OFFSET(Item, flags, 0x0c);
ASSERT_OFFSET(Item, price, 0x10);

/* The run Weapon, Armor and Accessory open with. */
typedef struct ItemHeader {
    u8 name[ITEM_NAME_LENGTH];
    u8 equipability; /* EquipFlags */
    u8 flags;        /* Item_GetFlags; bit tests in func_801AF494 */
} ItemHeader;

ASSERT_SIZE(ItemHeader, 0x0E);

typedef struct Weapon {
    ItemHeader header;
    u8         kind;    /* low nibble selects the icon in func_801AF800 via Item_GetKind */
    u8         element; /* ElementFlags */
    u8         weight;
    u8         sound; /* cue-table index in battle/battle/15 func_800AB834 and func_800AB910 */
    u8         power;
    u8         unk_13;
    u16        description; /* Item_GetDescription, category ITEM_CAT_WEAPON */
    u16        price;
} Weapon;

ASSERT_OFFSET(Weapon, description, 0x14);
ASSERT_SIZE(Weapon, WEAPON_STRIDE);
ASSERT_OFFSET(Weapon, header, 0x00);
ASSERT_OFFSET(Weapon, element, 0x0f);
ASSERT_OFFSET(Weapon, weight, 0x10);
ASSERT_OFFSET(Weapon, power, 0x12);
ASSERT_OFFSET(Weapon, price, 0x16);

typedef struct Armor {
    ItemHeader header;
    u8         equip_type; /* ArmorType */
    u8         weight;
    u8         power;
    u8         unk_11;
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

typedef struct Accessory {
    ItemHeader header;
    u8         kind; /* low nibble selects the icon in func_801AF800 via Item_GetKind */
    u8         weight;
    u16        description; /* Item_GetDescription, category ITEM_CAT_ACCESSORY */
    u16        price;
} Accessory;

ASSERT_OFFSET(Accessory, description, 0x10);
ASSERT_SIZE(Accessory, ACCESSORY_STRIDE);
ASSERT_OFFSET(Accessory, header, 0x00);
ASSERT_OFFSET(Accessory, weight, 0x0f);
ASSERT_OFFSET(Accessory, price, 0x12);

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
    ITEM_HEALING_HERB  = 3,
    ITEM_VITAMIN       = 4,
    ITEM_MULTIVITAMIN  = 5,
    ITEM_WISDOM_SEED   = 7,
    ITEM_WISDOM_FRUIT  = 8,
    ITEM_ANTIDOTE      = 10,
    ITEM_PANACEA       = 13,
    ITEM_MOON_TEARS    = 15,
    ITEM_FIRECRACKER   = 21,
    ITEM_ICICLE        = 22,
    ITEM_LIFE_SHARD    = 25,
    ITEM_MAGIC_SHARD   = 26,
    ITEM_POWER_FOOD    = 27,
    ITEM_PROTEIN       = 28,
    ITEM_SWALLOW_EYE   = 29,
    ITEM_FISH_HEAD     = 30,
    ITEM_MOXA          = 31,
    ITEM_SHALY_SEED    = 35,
    ITEM_VINEGAR       = 36,
    ITEM_BEEF_JERKY    = 39,
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
    ITEM_MARTIAN_SQUID = 63,
    ITEM_ANGLER        = 73,
    ITEM_MACKEREL      = 77,
    ITEM_HORSERADISH   = 86,
    ITEM_FAERIE_TIARA  = 87,
    ITEM_SKILL_INK     = 88,
    ITEM_FLOWER_JEWEL  = 89,
    ITEM_WATER_JUG     = 91,
} ItemId;

/* The weapon table ids (category ITEM_CAT_WEAPON). Names from the GAME.EMI record tables. */
typedef enum WeaponId {
    WEAPON_DEADLY_BLADE  = 13,
    WEAPON_DEMONSBANE    = 19,
    WEAPON_SEEKING_SWORD = 21,
    WEAPON_DRAGON_BLADE  = 22,
    WEAPON_HOLY_AVENGER  = 23,
    WEAPON_ASHURAS_SWORD = 26,
    WEAPON_HIDDENDAGGER  = 27,
    WEAPON_MAGICIAN_ROD  = 32,
    WEAPON_BERYL_ROD     = 37,
    WEAPON_BLESSED_STAFF = 39,
    WEAPON_OUROBOROS     = 40,
    WEAPON_ARIES_SPEAR   = 51,
    WEAPON_GUNGINIR      = 52,
    WEAPON_DRAGON_SPEAR  = 53,
    WEAPON_DRAGONFANG    = 64,
    WEAPON_THIEVES_KNIFE = 65,
    WEAPON_SLICER        = 67,
    WEAPON_LIFESTEALER   = 68,
    WEAPON_FLAME_CHRYSM  = 71,
    WEAPON_SLEEP_SHELLS  = 74,
    WEAPON_HE_SHELLS     = 75,
    WEAPON_FLASH_SHELLS  = 76,
    WEAPON_HOMING_BOMB   = 77,
    WEAPON_AP_SHELLS     = 78,
    WEAPON_GAS_SHELLS    = 79,
    WEAPON_GHOSTBUSTER   = 81,
    WEAPON_BEAST_SPEAR   = 82,
} WeaponId;

/* The armor table ids (category ITEM_CAT_ARMOR). Names from the GAME.EMI record tables. */
typedef enum ArmorId {
    ARMOR_NOTHING          = 0,
    ARMOR_BREASTPLATE      = 8,
    ARMOR_ASBESTOS_ARMOR   = 12,
    ARMOR_MAGMA_ARMOR      = 15,
    ARMOR_ROBE_OF_WIND     = 17,
    ARMOR_PHANTOM_DRESS    = 19,
    ARMOR_BLIZZARD_MAIL    = 20,
    ARMOR_SAGES_FROCK      = 22,
    ARMOR_HOLY_ROBE        = 24,
    ARMOR_BURGLAR_GARB     = 25,
    ARMOR_FORCE_ARMOR      = 27,
    ARMOR_GIDEONS_GARB     = 28,
    ARMOR_DIANAS_DRESS     = 29,
    ARMOR_DRAGON_ARMOR     = 30,
    ARMOR_LIFE_ARMOR       = 31,
    ARMOR_MIST_ARMOR       = 32,
    ARMOR_MITHRIL_HELM     = 39,
    ARMOR_LAUREL           = 40,
    ARMOR_TIGERS_CAP       = 44,
    ARMOR_SUN_MASK         = 45,
    ARMOR_LACQUER_HELM     = 46,
    ARMOR_SILVER_TIARA     = 47,
    ARMOR_DIVINE_HELM      = 48,
    ARMOR_DRAGON_HELM      = 49,
    ARMOR_FLAME_SHIELD     = 57,
    ARMOR_ICE_SHIELD       = 59,
    ARMOR_SPIKED_GAUNTLETS = 60,
    ARMOR_PROTECTORS       = 62,
    ARMOR_MIND_SHIELD      = 64,
    ARMOR_DRAGON_SHIELD    = 65,
    ARMOR_ARIES_GLOVES     = 66,
    ARMOR_MANLY_CLOTHES    = 67,
} ArmorId;

/* The accessory table ids (category ITEM_CAT_ACCESSORY). Names from the GAME.EMI record tables. */
typedef enum AccessoryId {
    ACCESSORY_NOTHING      = 0,
    ACCESSORY_TITAN_BELT   = 1,
    ACCESSORY_HIGH_BOOTS   = 2,
    ACCESSORY_SPEED_BOOTS  = 3,
    ACCESSORY_WISDOM_RING  = 4,
    ACCESSORY_LIONS_BELT   = 5,
    ACCESSORY_RING_OF_ICE  = 10,
    ACCESSORY_RING_OF_FIRE = 11,
    ACCESSORY_THUNDER_RING = 12,
    ACCESSORY_TALISMAN     = 13,
    ACCESSORY_DIAMOND_RING = 14,
    ACCESSORY_LIFE_SANDALS = 15,
    ACCESSORY_LIGHT_BANGLE = 16,
    ACCESSORY_BARRIER_RING = 17,
    ACCESSORY_HAWK_S_RING  = 18,
    ACCESSORY_ARTEMIS_CAP  = 19,
    ACCESSORY_CUPIDS_LYRE  = 22,
    ACCESSORY_IVORY_CHARM  = 23,
    ACCESSORY_SOUL_GEM     = 24,
    ACCESSORY_SHAMAN_SRING = 25,
    ACCESSORY_SPIRIT_RING  = 26,
    ACCESSORY_COUPONS      = 27,
} AccessoryId;

/* The vital item table ids (category ITEM_CAT_VITAL). Names from the GAME.EMI record tables. */
typedef enum VitalItemId {
    VITAL_ITEM_FLIER        = 1,
    VITAL_ITEM_EGG          = 3,
    VITAL_ITEM_GUILD_LETTER = 5,
    VITAL_ITEM_GUILD_BADGE  = 7,
    VITAL_ITEM_SEA_CHARTS   = 10,
    VITAL_ITEM_KEY          = 11,
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
extern volatile Weapon    g_Weapons[];
extern u8                 D_801C90E9[]; /* the weapon row's flags byte */
extern u8                 D_801C90F2;   /* the weapon row's price halfword */
/* D_801C98A4 */
extern volatile Armor     g_Armors[];
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
