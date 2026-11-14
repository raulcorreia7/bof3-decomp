#ifndef GAME_RECORDS_H
#define GAME_RECORDS_H

#include "types.h"
#include "sys/task.h"
#include "common/fixed.h"
#include "common/vector.h"

/* Counts, row sizes and array lengths of the fixed game tables, in the units
 * the loaders use. The loaders and the menu/party code index these; the record
 * types live beside their subsystem: character, item, ability, enemy, gene and
 * fairy. */

/* The field slot table at 0x80143FC8: 20 rows of 0x74 bytes. A slot is claimed
 * by Actor_FindFreeSlot, filled by Actor_Create and Char_SpawnActor, and
 * cleared by Actor_Free(s). The frontend cues, the staged scene objects and
 * the area030 fishing actors all use the same rows. The position words are the
 * same 16.16 coordinates as the field actor's (sys/actor.h): the
 * ground height from Area_SampleHeight sits in the halfword at +0x3E.
 *
 * The allocator's result is the actor slot. Callers test it against 0xFF for none. No retail string names the table. */
#define ACTOR_SLOT_SIZE                0x74
#define ACTOR_SLOT_COUNT               20

/* Lengths of the arrays inside the records. */
#define CHARACTER_NAME_LENGTH          5
#define ITEM_NAME_LENGTH               12
#define ABILITY_NAME_LENGTH            12
#define SHOP_STOCK_MAX                 11
#define MANILLO_FISH_COUNT             3
#define MANILLO_TRADE_COUNT            10
#define CHARACTER_ACCESSORY_COUNT      2
#define CHARACTER_ABILITY_COUNT        10 /* per ability class: healing, assist, attack, skill */
#define CHARACTER_LEVEL_MODIFIER_COUNT 6
#define MASTER_SKILL_COUNT             6
#define ENEMY_NAME_LENGTH              8
#define ENEMY_AI_PARAMETER_COUNT       7
#define ENEMY_SKILL_COUNT              8
#define ENEMY_AI_COUNT                 4
#define ENCOUNTER_ENEMY_COUNT          8

#define MASTER_COUNT                   17
#define DRAGON_POINTER_COUNT           10

#define ENEMY_COUNT                    1400
#define ENCOUNTER_COUNT                1600
#define CHEST_COUNT                    224
#define GENE_COUNT                     17
#define CHRYSM_COUNT                   13
#define FAIRY_COUNT                    720
#define MANILLO_ITEM_COUNT             165
#define MANILLO_STOCK_COUNT            16

#define FAIRY_GIFT_COUNT               20
#define FAIRY_EXPLORE_COUNT            48
#define FAIRY_PRIZE_COUNT              48

#define ITEM_COUNT                     92
#define WEAPON_COUNT                   83
#define ARMOR_COUNT                    68
#define ACCESSORY_COUNT                52
#define VITAL_ITEM_COUNT               16
#define SHOP_COUNT                     40
#define ABILITY_COUNT                  228
#define LEVEL_COUNT                    693
#define LEVEL_GROWTH_CHARACTER_COUNT   7
#define LEVEL_GROWTH_LEVEL_COUNT       99

#define PARTY_RECORD_STRIDE            0xa4
#define MASTER_SKILLS_STRIDE           0x0c
#define MASTER_STATS_STRIDE            0x06
#define ENEMY_STRIDE                   0x88
#define ENCOUNTER_STRIDE               0x09
#define CHEST_STRIDE                   0x03
#define FAIRY_STRIDE                   0x09
#define MANILLO_ITEM_STRIDE            0x08
#define MANILLO_STOCK_STRIDE           0x0a
#define FAIRY_GIFT_STRIDE              0x04
#define FAIRY_EXPLORE_STRIDE           0x02
#define FAIRY_PRIZE_STRIDE             0x02
#define ITEM_STRIDE                    0x12
#define VITAL_ITEM_STRIDE              0x10
#define WEAPON_STRIDE                  0x18
#define ARMOR_STRIDE                   0x16
#define ACCESSORY_STRIDE               0x14
#define SHOP_STRIDE                    0x17
#define ABILITY_STRIDE                 0x14
#define LEVEL_STRIDE                   0x08
#define LEVEL_GROWTH_CHARACTER_STRIDE  (LEVEL_GROWTH_LEVEL_COUNT * LEVEL_STRIDE)

/* The SpawnedActor.type values that have a named handler in g_ActorTypes. */
typedef enum ActorType {
    ACTOR_TYPE_FACING_PROBE = 0x3A,
} ActorType;

typedef struct SpawnedActor {
    TaskHeader header;       /* 0x00 */
    u8         unk_03;       /* 0x03 */
    u8         unk_04;       /* 0x04 */
    u8         type;         /* 0x05 actor type: 0x0F/0x10/0x1E/0x32/0x69; handler index; accessory count */
    u8         unk_06;       /* 0x06 area id in area030; slot index in game00 */
    u8         unk_07;       /* 0x07 */
    u8         unk_08;       /* 0x08 */
    u8         layer;        /* 0x09 layer: 0x20/0x40/0x60/0x90/0xFF */
    u8         unk_0A;       /* 0x0A */
    u8         link;         /* 0x0B index of the linked slot */
    s32        scene_step;   /* 0x0C scenario step */
    s32        selection;    /* 0x10 frontend selection */
    s32        unk_14;       /* 0x14 */
    s32        counter_18;   /* 0x18 */
    s32        counter_1C;   /* 0x1C */
    s32        unk_20;       /* 0x20 - seeded with 0x500000 */
    u8         unk_24;       /* 0x24 */
    u8         pad_25[2];    /* 0x25-0x26 */
    u8         unk_27;       /* 0x27 */
    u8         unk_28;       /* 0x28 */
    u8         unk_29;       /* 0x29 cleared when the slot is rebuilt */
    u8         pad_2A[2];    /* 0x2A-0x2B */
    u16        unk_2C;       /* 0x2C */
    s16        unk_2E;       /* 0x2E */
    s16        unk_30;       /* 0x30 */
    u8         pad_32[2];    /* 0x32-0x33 */
    Coord3     pos;          /* 0x34 world position */
    u8         pad_40[0x0A]; /* 0x40-0x49 */
    u8         unk_4A;       /* 0x4A */
    u8         pad_4B[0x19]; /* 0x4B-0x63 */
    Point3l    camera_angle; /* 0x64 */
    u8         pad_70[4];    /* 0x70-0x73 */
} SpawnedActor;

ASSERT_SIZE(SpawnedActor, ACTOR_SLOT_SIZE);
ASSERT_OFFSET(SpawnedActor, header, 0x00);
ASSERT_OFFSET(SpawnedActor, type, 0x05);
ASSERT_OFFSET(SpawnedActor, layer, 0x09);
ASSERT_OFFSET(SpawnedActor, unk_2C, 0x2C);
ASSERT_OFFSET(SpawnedActor, scene_step, 0x0C);
ASSERT_OFFSET(SpawnedActor, selection, 0x10);
ASSERT_OFFSET(SpawnedActor, unk_20, 0x20);
ASSERT_OFFSET(SpawnedActor, pos, 0x34);
ASSERT_OFFSET(SpawnedActor, camera_angle, 0x64);

extern SpawnedActor g_SpawnedActors[ACTOR_SLOT_COUNT];

#endif
