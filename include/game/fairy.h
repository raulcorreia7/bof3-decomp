#ifndef GAME_FAIRY_H
#define GAME_FAIRY_H

#include "types.h"
#include "game/records.h"

#define FAIRY_JOB_COUNT  60
#define FAIRY_JOB_STRIDE 0x8

/* The fairy village's data tables: the 720-fairy roster and the reward tables
 * that the communication minigame reads. `FAIRY_*` in game/records.h holds the
 * counts and strides. @source: wiki:data/records#area-data (all 720
 * roster entries; the reward offsets).
 *
 * The roster lives in `COMMU00.EMI`; the gift shop's 20 unlocks are at
 * `0x848` and the 48 exploration rewards at `0x4218`. The prize table is in
 * `COMMU02.EMI` at `0x2D900`; its runtime load mapping is unverified. */

typedef struct Fairy {
    u8 name[5];
    u8 stats[4]; /* four stat bytes; the roles are unknown */
} Fairy;

ASSERT_SIZE(Fairy, FAIRY_STRIDE);

/* Gift-shop unlocks are battle counts; exploration rewards use the same item
 * IDs. */
typedef struct FairyGift {
    u16 num_battles; /* battles before the gift unlocks */
    u8  item_index;
    u8  item_type;
} FairyGift;

ASSERT_SIZE(FairyGift, FAIRY_GIFT_STRIDE);

/* One exploration reward: an item id and its category. */
typedef struct FairyExploreReward {
    u8 item_index;
    u8 item_type;
} FairyExploreReward;

ASSERT_SIZE(FairyExploreReward, FAIRY_EXPLORE_STRIDE);

/* A `COMMU02.EMI` prize row: the same two bytes as an exploration reward. */
typedef struct FairyPrize {
    u8 item_index;
    u8 item_type;
} FairyPrize;

ASSERT_SIZE(FairyPrize, FAIRY_PRIZE_STRIDE);

typedef enum FairyJobType {
    FAIRY_JOB_IDLE  = 0,
    FAIRY_JOB_HUNT  = 9,
    FAIRY_JOB_CLEAR = 10,
    FAIRY_JOB_BUILD = 11,
} FairyJobType;

/* A village job and the battle count when it last advanced. */
typedef struct FairyJob {
    u8  active;
    u8  type;
    u8  record_state;
    u8  unk_03;
    u32 progress_anchor;
} FairyJob;

ASSERT_SIZE(FairyJob, FAIRY_JOB_STRIDE);

/* D_801455C8 */
extern FairyJob g_FairyJobs[FAIRY_JOB_COUNT];

#endif
