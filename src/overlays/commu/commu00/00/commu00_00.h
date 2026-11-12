#ifndef OVERLAY_ETC_COMMU00_00_H
#define OVERLAY_ETC_COMMU00_00_H

/* The fairy-village communication minigame's local declarations: the 60 stat
 * rows at 0x801F2700 and the 60 job rows at 0x801455C8, the culture and reward
 * tables, its handlers and prototypes. The 720-entry roster record is in
 * game/fairy.h; @source: wiki:data/records#area-data has the reward offsets. Only
 * this image includes the file. */

#include "shared/etc.h"
#include "area/spad.h"
#include <stdio.h>
#include <string.h>

/* The fairy-village roster this overlay owns: the 60 stat rows at 0x801F2700
 * and the 60 job rows that pair with them at 0x801455C8. */
#define FAIRY_VILLAGE_COUNT                   60

/* The village culture levels, 0 to 6 (D_801455C4, gated by `sltiu 7`). */
#define FAIRY_CULTURE_MAX                     6

/* The exploration trip types: the success roll each one needs
 * (D_801EEC04, read signed by func_801EF784) and the label cap that bounds
 * its random label roll (D_801EEC08, read by func_801F03D0). */
#define FAIRY_EXPLORE_TRIP_NEAR               0
#define FAIRY_EXPLORE_TRIP_MIDDLE             1
#define FAIRY_EXPLORE_TRIP_FAR                2

#define FAIRY_EXPLORE_SUCCESS_NEAR            65
#define FAIRY_EXPLORE_SUCCESS_MIDDLE          55
#define FAIRY_EXPLORE_SUCCESS_FAR             15

#define FAIRY_LABEL_CAP_NEAR                  15
#define FAIRY_LABEL_CAP_MIDDLE                20
#define FAIRY_LABEL_CAP_FAR                   25

/* The job-progress step the copy shop needs before it opens (D_801455C3). */
#define FAIRY_JOB_PROGRESS_COPY               0xA

/* The fairy job row: 8 bytes, the stride the village code walks
 * (func_801EF110, func_801EFA50). */
#define FAIRY_JOB_SIZE                        0x8
#define FAIRY_VARIANT_SIZE                    0x6
#define FAIRY_VILLAGE_HEAD_SIZE               0xC
#define FAIRY_EXPLORE_TRIP_COUNT              3
#define FAIRY_REWARD_ROLL_SIZE                4
#define FAIRY_VILLAGE_HEADER_DATA_SIZE        0x60
#define FAIRY_VILLAGE_FMT_SIZE                4

/* The overlay's shared data block at 0x801F24FC..0x801F2950, read through the
 * symbol views in the data block. Each define is one member's row count. */
#define FAIRY_VILLAGE_DATA_SIZE               0x454
#define FAIRY_VILLAGE_RESOURCE_ID_COUNT       6
#define FAIRY_CULTURE_LEVEL_COUNT             7
#define FAIRY_VILLAGE_JOB_PROGRESS_CAP_COUNT  13
#define FAIRY_VILLAGE_COPY_CLASS_COUNT        8
#define FAIRY_VILLAGE_COPY_CLASS_FIELD_COUNT  3
#define FAIRY_VILLAGE_MUSIC_LEVEL_CAP_COUNT   8
#define FAIRY_VILLAGE_TASK_ROW_COUNT          20
#define FAIRY_VILLAGE_TASK_ROW_FIELD_COUNT    3
#define FAIRY_VILLAGE_VARIANT_ROW_COUNT       8
#define FAIRY_VILLAGE_VARIANT_ROW_FIELD_COUNT 3
#define FAIRY_VILLAGE_VARIANT_VARIANT_COUNT   3
#define FAIRY_COMMU01_STEP_COUNT              6
#define FAIRY_GIFT_STEP_COUNT                 3
#define FAIRY_EXPLORE_REWARD_STEP_COUNT       1
#define FAIRY_COMMU02_STEP_COUNT              5
#define FAIRY_COMMU02_ENTRY_COUNT             4
#define FAIRY_COMMU03_STEP_COUNT              5
#define FAIRY_COMMU04_STEP_COUNT              7
#define FAIRY_COMMU05_STEP_COUNT              5
#define FAIRY_VILLAGE_COPY_ITEM_COUNT         16

/* The village messages the fairy steps request through Message_StartAreaMessage. */
#define FAIRY_MESSAGE_EXPLORE_FOUND_ITEM      0x4F
#define FAIRY_MESSAGE_EXPLORE_BAG_FULL        0x50
#define FAIRY_MESSAGE_EXPLORE_NO_REWARD       0x52
#define FAIRY_MESSAGE_PLAY_RECORD             0x55
#define FAIRY_MESSAGE_PLAY_RECORD_COUNTS      0x56
#define FAIRY_MESSAGE_GIFT_RECEIVED           0x96
#define FAIRY_MESSAGE_NO_GIFT_YET             0x98
#define FAIRY_VILLAGE_VARIANT_COUNTER_COUNT   8
#define FAIRY_VILLAGE_LABEL_ROW_COUNT         3
#define FAIRY_VILLAGE_LABEL_FIELD_COUNT       3

/* The loaded work-area pointer; the pointee is the unit's Actor. */
#define FAIRY_VILLAGE_ACTIVE_UI               D_801F2948

/* The kind table read without volatile semantics: the cell is declared
 * volatile for its other users, so the units that walk it take a plain view. */
/* Byte at the start of each 8-byte record-kind entry. */
#define VILLAGE_ROOM_SUBTYPE(index)           (D_801457A9[(index) * 8])
/* Unsigned view: the cell is declared s8, but the original reads and writes it
 * unsigned (lbu/sb). */
/* FAKE: retail reads the state byte unsigned. */
#define FAIRY_EVENT_STEP                      (*(u8*)&g_SceneEventStep)

/* Variant row: message id and item id followed by the pending count. */
typedef struct FairyVariant {
    u16 message_id;
    u16 item_id;
    u16 count;
} FairyVariant;

ASSERT_SIZE(FairyVariant, FAIRY_VARIANT_SIZE);
ASSERT_OFFSET(FairyVariant, message_id, 0x00);
ASSERT_OFFSET(FairyVariant, item_id, 0x02);
ASSERT_OFFSET(FairyVariant, count, 0x04);

/* The payload prologue at 0x801EEC00: the type-0 EMI loader compares the
 * first word with the archive TOC's cached first word
 * (@source: wiki:formats/emi). The two threshold arrays are read as signed
 * bytes: D_801EEC04[0..2] by func_801EF784 and D_801EEC08[0..2] by
 * func_801F03D0. */
typedef struct FairyVillageHead {
    u32 id;                                              /* 0x00; TOC cached first word, 0x18 */
    s8  explore_threshold[FAIRY_EXPLORE_TRIP_COUNT + 1]; /* 0x04 D_801EEC04; 65, 55, 15: the success roll per trip type */
    s8  label_cap[FAIRY_EXPLORE_TRIP_COUNT];             /* 0x08 D_801EEC08; values 15/20/25 */
    u8  pad_0B;
} FairyVillageHead;

ASSERT_SIZE(FairyVillageHead, FAIRY_VILLAGE_HEAD_SIZE);
ASSERT_OFFSET(FairyVillageHead, explore_threshold, 0x04);
ASSERT_OFFSET(FairyVillageHead, label_cap, 0x08);

/* One exploration reward row (Fairy_RollExploreReward): the roll the group starts at,
 * then the three group weights. */
typedef struct FairyRewardRoll {
    u8 value;
    u8 weights[FAIRY_EXPLORE_TRIP_COUNT];
} FairyRewardRoll;

ASSERT_SIZE(FairyRewardRoll, FAIRY_REWARD_ROLL_SIZE);
ASSERT_OFFSET(FairyRewardRoll, weights, 0x01);

/* The 96-byte header-data block: the "%d" format, the 20 gift rows
 * Fairy_GrantGift copies, and the 3 exploration reward rows Fairy_RollExploreReward
 * copies. */
typedef struct FairyVillageHeaderData {
    char            fmt[FAIRY_VILLAGE_FMT_SIZE];     /* 0x00 D_801EEC44 "%d" */
    FairyGift       gifts[FAIRY_GIFT_COUNT];         /* 0x04 D_801EEC48 */
    FairyRewardRoll rolls[FAIRY_EXPLORE_TRIP_COUNT]; /* 0x54 D_801EEC98 */
} FairyVillageHeaderData;

ASSERT_SIZE(FairyVillageHeaderData, FAIRY_VILLAGE_HEADER_DATA_SIZE);
ASSERT_OFFSET(FairyVillageHeaderData, gifts, 0x04);
ASSERT_OFFSET(FairyVillageHeaderData, rolls, 0x54);

/* The overlay's shared data block, read through the symbol views listed
 * beside each member. The step arrays are the scene step tables the village dispatches through. */
typedef struct FairyVillageData {
    u16                 resource_ids[FAIRY_VILLAGE_RESOURCE_ID_COUNT]; /* 0x000 D_801F24FC; source_index % 6 */
    u8                  unk_00C[12];                                   /* 0x00C; no static reader */
    u16                 culture_threshold[FAIRY_CULTURE_LEVEL_COUNT];  /* 0x018 D_801F2514; 15,18,21,24,27,30,40 */
    u8                  pad_026;
    u8                  job_progress_cap[FAIRY_VILLAGE_JOB_PROGRESS_CAP_COUNT];                                                                    /* 0x027 D_801F2523; the cap per job-progress step */
    u16                 copy_class[FAIRY_VILLAGE_COPY_CLASS_COUNT][FAIRY_VILLAGE_COPY_CLASS_FIELD_COUNT];                                          /* 0x034 D_801F2530/D_801F2532/D_801F2534;
                                                     max price, battles, multiplier */
    u8                  music_level_cap[FAIRY_VILLAGE_MUSIC_LEVEL_CAP_COUNT];                                                                      /* 0x064 D_801F2560; the level cap per culture */
    u8                  task_rows[FAIRY_VILLAGE_TASK_ROW_COUNT][FAIRY_VILLAGE_TASK_ROW_FIELD_COUNT];                                               /* 0x06C D_801F2568 */
    u8                  variant_rows[FAIRY_VILLAGE_VARIANT_ROW_COUNT][FAIRY_VILLAGE_VARIANT_ROW_FIELD_COUNT][FAIRY_VILLAGE_VARIANT_VARIANT_COUNT]; /* 0x0A8 D_801F25A4 */
    /* 0xF0 */ Callback commu01_steps[FAIRY_COMMU01_STEP_COUNT];                                                                                   /* 0x0F0 g_FairyCommu01States */
    Callback            gift_steps[FAIRY_GIFT_STEP_COUNT];                                                                                         /* 0x108 g_FairyGiftStates */
    Callback            explore_reward_steps[FAIRY_EXPLORE_REWARD_STEP_COUNT];                                                                     /* 0x114 g_FairyExploreRewardStates */
    u8                  unk_118[4];
    FairyExploreReward  explore_rewards[FAIRY_EXPLORE_COUNT];                                   /* 0x11C D_801F2618/D_801F2619 */
    Callback            commu02_steps[FAIRY_COMMU02_STEP_COUNT];                                /* 0x17C g_FairyCommu02States */
    const Callback      commu02_entries[FAIRY_COMMU02_ENTRY_COUNT];                             /* 0x190 g_FairyCommu02Events */
    Callback            commu03_steps[FAIRY_COMMU03_STEP_COUNT];                                /* 0x1A0 g_FairyCommu03States */
    Callback            commu04_steps[FAIRY_COMMU04_STEP_COUNT];                                /* 0x1B4 g_FairyCommu04States */
    u16                 copy_item[FAIRY_VILLAGE_COPY_ITEM_COUNT];                               /* 0x1D0 D_801F26CC/D_801F26CE/D_801F26D0 */
    Callback            commu05_steps[FAIRY_COMMU05_STEP_COUNT];                                /* 0x1F0 g_FairyCommu05States */
    Fairy               fairies[FAIRY_VILLAGE_COUNT];                                           /* 0x204 g_Fairies/D_801F2705/D_801F2706/D_801F2708 */
    u8                  unk_420[12];                                                            /* 0x420; no static reader */
    volatile u8         variant_counter[FAIRY_VILLAGE_VARIANT_COUNTER_COUNT];                   /* 0x42C D_801F2928 */
    u16                 labels[FAIRY_VILLAGE_LABEL_ROW_COUNT][FAIRY_VILLAGE_LABEL_FIELD_COUNT]; /* 0x434 D_801F2930 */
    u8                  pad_446[2];
    u8                  state_448[2]; /* 0x448 D_801F2944/D_801F2945 */
    u8                  pad_44A[2];
    void*               active_ui;    /* 0x44C D_801F2948 (FAIRY_VILLAGE_ACTIVE_UI) */
    u8                  state_450[4]; /* 0x450 D_801F294C..D_801F294F */
} FairyVillageData;

ASSERT_SIZE(FairyVillageData, FAIRY_VILLAGE_DATA_SIZE);
ASSERT_OFFSET(FairyVillageData, culture_threshold, 0x018);
ASSERT_OFFSET(FairyVillageData, job_progress_cap, 0x027);
ASSERT_OFFSET(FairyVillageData, copy_class, 0x034);
ASSERT_OFFSET(FairyVillageData, music_level_cap, 0x064);
ASSERT_OFFSET(FairyVillageData, task_rows, 0x06C);
ASSERT_OFFSET(FairyVillageData, variant_rows, 0x0A8);
ASSERT_OFFSET(FairyVillageData, explore_rewards, 0x11C);
ASSERT_OFFSET(FairyVillageData, fairies, 0x204);
ASSERT_OFFSET(FairyVillageData, variant_counter, 0x42C);
ASSERT_OFFSET(FairyVillageData, labels, 0x434);

/* Retail-address data symbols, in address order. */
extern u8               D_801448F2;
extern s32              D_80145030;
extern s32              D_8014503C;
extern s32              D_801455A8;
extern u32              D_801455AC;
extern u32              D_801455B0;
extern u32              D_801455B4;
extern s32              D_801455B8;
extern s32              D_801455BC;
extern u16              D_801455C0;
extern s8               D_801455C2;
extern u8               D_801455C6;
extern const u8         g_FairyRooms[];
extern u8               D_801457A9[];
extern u8               D_801457AA[];
extern u8               D_801457AB[];
extern s32              D_801457EC; /* end of the group table at 0x801457AC; func_801EF52C and func_801EFEA8 compare a row pointer
                           against it */
extern u8               D_80145E30[];
extern u8               D_80145E48[];
extern u8               D_80145E60[];
extern ShopStock        g_GameShopStock[SHOP_COUNT];
extern s8               D_801EEC08[];
extern char             D_801EEC44[];
extern u8               g_FairyGifts[];
extern u8               D_801EEC98[];
extern u8               D_801F2458[];
extern const u16        D_801F24FC[];
extern u16              D_801F2514[];
extern u8               D_801F2523[];
/* The copy-class cells of the overlay's data block: each class's max price,
 * battle count and multiplier. The retail materializes every cell through its
 * own symbol and steps six bytes per class (func_801EFA50). */
extern u8               D_801F2560; /* the bar limit byte; func_801EFEA8 reads it with lbu at 0x801EFF14 and 0x801EFFE8 */
extern u8               D_801F2568[][3];
extern u8               D_801F25A4[][3][3];
/* D_801F25EC */
extern Callback         g_FairyCommu01States[FAIRY_COMMU01_STEP_COUNT];
/* D_801F2604 */
extern Callback         g_FairyGiftStates[FAIRY_GIFT_STEP_COUNT];
/* D_801F2610 */
extern Callback         g_FairyExploreRewardStates[FAIRY_EXPLORE_REWARD_STEP_COUNT];
extern u8               g_FairyExploreRewards[];
extern u8               D_801F2619[];
/* D_801F2678 */
extern Callback         g_FairyCommu02States[FAIRY_COMMU02_STEP_COUNT];
/* D_801F268C */
extern const Callback   g_FairyCommu02Events[FAIRY_COMMU02_ENTRY_COUNT];
/* D_801F269C */
extern Callback         g_FairyCommu03States[FAIRY_COMMU03_STEP_COUNT];
/* D_801F26B0 */
extern Callback         g_FairyCommu04States[FAIRY_COMMU04_STEP_COUNT];
extern FairyVariant     D_801F26CC[1];
/* D_801F26EC */
extern Callback         g_FairyCommu05States[FAIRY_COMMU05_STEP_COUNT];
extern u8               D_801F2706[][9];
extern u8               D_801F2708[];
extern volatile u8      D_801F2928[1];
/* Label table rows are the three age buckets; each row holds one entry per
 * record variant. */
extern u16              D_801F2930[][3];
extern u8               D_801F2944;
extern u8               D_801F2945;
extern u8               D_801F294F;
extern FairyVillageData D_801F24FC_Data;

/* The scratchpad work pointer; each overlay types the pointee for its mode. */

bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
void func_801D3568(void);
void func_801D5034(void);
void func_801D5D5C(void);
void Fairy_InitVillage(void);
void Fairy_AddRooms(void);
void func_801EEEF0(u32 row_index);
void func_801EF110(s32 battle_count);
void func_801EF214(void);
void func_801EF52C(void);
s32  func_801EF784(void);
s32  func_801EFA50(void);
s32  func_801EFEA8(void);
void Fairy_JoinVillage(void);
void func_801F01F4(void);
void func_801F0320(void);
void Fairy_StartJobs(void);
void func_801F0718(u8 source_index, u8 task_index);
/* func_801F08D8 */
void Fairy_SpawnWorker(u8 source_index, u8 task_index);
void func_801F0BF4(u8 task_index);
void func_801F0C6C(u8 task_index, u8 record_kind_index);
void func_801F0D3C(u8 task_index, u8 record_kind_index);
void func_801F0E1C(u8 task_index, u8 record_kind_index);
void func_801F0EC8(u8 task_index);
void func_801F0F08(u8 source_index, u8 task_index, u8 record_kind_index);
void func_801F0FBC(u8 source_index, u8 task_index, u8 record_kind_index);
void func_801F1064(u8 task_index, u8 record_kind_index);
void func_801F1110(u8 task_index, u8 record_kind_index);
void func_801F1204(u8 task_index, u8 record_kind_index);
void func_801F1254(u8 task_index);
s32  func_801F1294(u8* active_ui);
s32  func_801F12C8(volatile Actor* slot);
s32  Fairy_ShowPlayRecordMessage(void);
s32  func_801F13B8(void);
s32  func_801F1444(u8* active_ui);
s32  func_801F1484(u8* active_ui);
s32  func_801F14C4(u8* active_ui);
s32  func_801F14F8(u8* active_ui);
s32  func_801F1538(u8* active_ui);
s32  func_801F1578(u8* active_ui);
s32  func_801F15B8(u8* active_ui);
s32  func_801F15F8(u8* active_ui);
void func_801F1638(void);
void func_801F1684(void);
void func_801F16F8(void);
void Fairy_LoadCommu01(void);
/* func_801F17A4 */
void Fairy_FinishEventLoad(void);
void Fairy_ReloadPartySprites(void);
void func_801F1874(void);
void Fairy_GrantGift(void);
void func_801F1AFC(void);
void func_801F1B30(void);
void Fairy_RollExploreReward(void);
void Fairy_LoadCommu02(void);
void func_801F1F10(void);
void func_801F1F4C(void);
void Fairy_LoadCommu03(void);
void func_801F205C(void);
void Fairy_LoadCommu04(void);
void Fairy_LoadCommu05(void);
void func_801F235C(void);

#endif
