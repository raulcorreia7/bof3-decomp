#ifndef BATTLE_RAM_H
#define BATTLE_RAM_H

/* Shared battle RAM layout: work-record bases and strides, call tables, ring and kind records
 * (@source: wiki:data/battle#where-the-records-are) */

#include "battle/records.h"
#include "psx/mem.h"
#include "types.h"

/* retail addresses */

/*
 * Evidenced in both battle/battle/03 and battle/battle/15. Per-image headers keep
 * their own target-specific accessors; these names describe addresses common
 * to both targets. Strides are struct sizes (hex). Addresses are fixed RAM
 * (hex).
 */

#define BATTLE_SPOILS_SIZE 0x3E

/* Raise a bit in the battle state word. A bare statement macro: the member
 * declares `flags` and runs the follow-up the bit starts. Kept: as an inline
 * the member loses its 24-byte frame (first instruction differs in 17 members);
 * the do/while form moves bytes. */
#define BATTLE_RAISE_STATE(flag) \
    flags = &g_BattleState;      \
    *flags |= (flag)

/* The party rows 0-2 and enemy rows 3-10 share one battler index space. */
#define COMBATANT_COUNT                   11
/* The drop list cap Battle_RollEnemyDrops walks. */
#define BATTLE_SPOILS_COUNT_MAX           15

/* func_801DB434 reads six threshold bytes per row. */
#define BATTLE_LEVEL_THRESHOLD_COUNT      6u

#define BATTLE_PARTY_SLOT_COUNT           3 /* player slots 0-2; enemy slots start at 3 */
#define BATTLE_PARTY_STRIDE               0x140
#define BATTLE_ENEMY_STRIDE               0x118
#define BATTLE_EFFECT_STRIDE              0x78
#define BATTLE_RING_STRIDE                0x08
#define BATTLE_KIND_STRIDE                0x14

#define PARTY_COMBATANT_BASE              0x80145E90u
#define ENEMY_COMBATANT_BASE              0x801EB630u
#define BATTLE_EFFECT_BASE                0x801EC330u

/* Parent base of the enemy records: ENEMY_COMBATANT_BASE - 3 * enemy stride, so
 * player slots 0-2 and enemy slots 3-10 share one battler index space. */
#define ENEMY_COMBATANT_PARENT_BASE       0x801EB2E8u

/*
 * Data tables every overlay loaded at 0x80096800 carries its own copy of
 * (battle/battle/15 and the boss archives). Each is indexed directly by the record id
 * and holds one byte per entry, so a table read is `table[id]`.
 */
#define BATTLE_ABILITY_CALL_TABLE         0x800B44F8u
#define BATTLE_ITEM_CALL_TABLE            0x800B45E0u
#define BATTLE_ITEM_ANIM_TABLE            0x800B6AC0u
/* Six u8 escape thresholds: 32, 36, 40, 44, 48, 52. */
#define BATTLE_ESCAPE_THRESHOLD_TABLE     0x800B44F0u
/* Eight u8 difficulty thresholds: 1, 2, 4, 8, 12, 16, 24, 48; indexed by the
 * ability record's high nibble at offset 0x0D. */
#define BATTLE_LEARNING_DIFFICULTY_TABLE  0x800B50DCu
/* Four-byte function pointers, indexed by accessory id - 1 (bound 0x17). */
#define BATTLE_ACCESSORY_CALL_TABLE       0x80149EC8u
/* The 0x40-stride action blocks GFX_StagePalette copies an action step into, one
 * per battler slot (index << 6). */
#define BATTLE_ACTION_BLOCK_TABLE         0x80035600u
/* The encounter block: formations and 0x88-stride enemy records from +0x48 (ENCOUNTER_ENEMIES in game/enemy.h). Block
 * +0xCA and +0xCB are the reach and height of enemy record +0x82 and +0x83. */
#define BATTLE_ENCOUNTER_TABLE            0x800E4000u

/* The enemy battler row for a battler slot: enemy slots begin after the party
 * slots, so slot 3 is the first enemy row. An lvalue, so reads, writes and
 * member access all use it. */
#define ENEMY_COMBATANT(slot)             (g_BattleEnemyBattlers[(slot) - BATTLE_PARTY_SLOT_COUNT])
/* A battler slot on the player side: slots 0-2 are the party rows. */
#define BATTLER_IS_PLAYER(slot)           ((slot) < BATTLE_PARTY_SLOT_COUNT)

/* The battle ended with the party's victory: the result bit the ending step
 * sets when no enemy is left. */
#define BATTLE_IS_VICTORY()               (g_BattleResult & BATTLE_RESULT_VICTORY)

#define BATTLE_SELECTION_RECORD_HANDLE(i) MEM(u8* volatile, 0x801EB5B4u + (u32)(i) * BATTLE_RING_STRIDE)

#define BATTLE_ACTIVE_WORK                ((PartyBattler*)D_801EB4E0)

/* A hit's target answers with a reprisal when its reprisal roll passes
 * (Character.stats.reprisal_chance, or the enemy's event_flags bit 2): the hit's
 * ending step sets REPRISAL_PENDING, the turn's closing step hands the action
 * to that battler, and the answer's own ending step sets REPRISAL_DONE so the
 * answer is not itself answered (func_801E020C, func_801E414C, func_801D43EC).
 * EFFECT_LOADING is held from the action's effect stream request
 * (EMI_LoaderStreamInitSlot) until the loader is ready (func_801D3F6C). */

/* The battle spoils record at 0x80146326: the base byte is the escape-attempt
 * counter the battle/battle/15 units read, the count of listed drops sits at +0x01,
 * the dropped item ids at +0x0E and their counts at +0x2E (Battle_RollEnemyDrops). */
typedef struct Spoils {
    u8  attempts; /* +0x00 escape attempts; battle/battle/15 reads this byte */
    u8  count;    /* +0x01 listed drops, capped at 15 */
    u8  pad_02[0xC];
    u16 items[16];  /* +0x0E dropped item ids */
    u8  counts[16]; /* +0x2E drops of each id */
} Spoils;

ASSERT_SIZE(Spoils, BATTLE_SPOILS_SIZE);
ASSERT_OFFSET(Spoils, count, 0x01);
ASSERT_OFFSET(Spoils, items, 0x0E);
ASSERT_OFFSET(Spoils, counts, 0x2E);

/* The battle's phase tuple at 0x801462E0: the mode selects the g_BattlePhases handler, the step runs inside it and
 * the sub-step inside the step. BattleSetEnding writes the three bytes together; the intro and panel code reset
 * step and sub-step together and advance the mode through one base. */
typedef struct BattlePhase {
    u8 mode;     /* 0x00 */
    u8 step;     /* 0x01 */
    u8 sub_step; /* 0x02 */
} BattlePhase;

ASSERT_SIZE(BattlePhase, 3);
ASSERT_OFFSET(BattlePhase, step, 0x01);
ASSERT_OFFSET(BattlePhase, sub_step, 0x02);

/* D_801462E0 */
extern BattlePhase g_BattlePhase;

/* The battle state word g_BattleState, read and written by both battle overlays
 * and the boss/bmagic handlers. Bit 3 (0x0008) is set by func_801D277C and
 * func_8009B828 and cleared by func_801D656C; no reader is known, so
 * it has no member. */
typedef enum BattleStateFlags {
    BATTLE_STATE_WINDOW_BUSY      = 1 << 1,
    BATTLE_STATE_EFFECT_PLAYING   = 1 << 2,
    BATTLE_STATE_COMMAND_ARMED    = 1 << 4,
    BATTLE_STATE_REPRISAL_PENDING = 1 << 6,
    BATTLE_STATE_CRITICAL         = 1 << 7,
    BATTLE_STATE_EFFECT_LOADING   = 1 << 10,
    BATTLE_STATE_AP_PAID          = 1 << 11,
    BATTLE_STATE_REPRISAL_DONE    = 1 << 12,
    BATTLE_STATE_DAMAGE_APPLIED   = 1 << 13,
    BATTLE_STATE_OVER             = 1 << 14,
    BATTLE_STATE_RELOAD_PARTY     = 1 << 15,
} BattleStateFlags;

/* The side mask func_800A9820 writes into D_80146384; the low values are one
 * battler slot (0-10). */
typedef enum BattleTargetFlags {
    BATTLE_TARGET_ENEMY_SIDE = 1 << 6,
    BATTLE_TARGET_PARTY_SIDE = 1 << 7,
    BATTLE_TARGET_BOTH_SIDES = BATTLE_TARGET_ENEMY_SIDE | BATTLE_TARGET_PARTY_SIDE,
} BattleTargetFlags;

/* The battle result byte D_80146328. */
typedef enum BattleResultFlags {
    BATTLE_RESULT_DEFEAT  = 1 << 0,
    BATTLE_RESULT_VICTORY = 1 << 1,
    BATTLE_RESULT_NO_BGM  = 1 << 3,
} BattleResultFlags;

extern s32          D_801459E8;
/* Battle frame/sequence word read by both battle overlays. */
/* D_801459F0 */
extern volatile u32 g_ScriptBank;
extern u8           D_80145A00;
extern s32          D_80145A04;
extern u8           D_80146229;
extern u16          D_8014622A;
extern u8           D_80146232;
/* Stock count owned by the main executable. */
extern u8           g_PartySize;
/* D_80146255 */
extern u8           g_BattlePartyOrder;
extern s16          D_801462AA;
/* D_801462E5 */
extern u8           g_BattleRowCursor;
/* D_801462ED */
extern u8           g_BattleBossFlags;
extern u8           D_801462EE;
/* D_801462F1 */
extern u8           g_BattleLivingPartyCount;
/* D_80146303. A unit that reads it as volatile (battle/battle/15) defines
 * BATTLE_COMMAND_COUNT_VOLATILE before its first include. Retail loads it signed
 * in battle/battle/03 func_801D1E8C and func_801D25A0 and unsigned elsewhere. */
#ifdef BATTLE_COMMAND_COUNT_VOLATILE
extern volatile u8 g_BattleCommandCount;
#else
extern u8 g_BattleCommandCount;
#endif
/* D_80146324 */
extern u8     g_BattleSurprise;
extern Spoils D_80146326;
/* D_8014632C */
extern u32    g_BattleSpoilsExp;
/* D_80146330 */
extern s32    g_BattleSpoilsZenny;

/* The kind of command the active battler runs; 2 and 3 are enemy AI states with no name yet. */
enum {
    BATTLE_ACTION_NONE    = 0,
    BATTLE_ACTION_ATTACK  = 1, /* a plain attack: Battle_ApplyDamage */
    BATTLE_ACTION_ABILITY = 4, /* g_BattleActionId indexes the ability table D_801CA71C */
    BATTLE_ACTION_ITEM    = 5, /* g_BattleActionId is category << 8 | item id */
};

/* D_80146375 */
extern volatile u8   g_BattleActionType;
extern u16           D_80146386;
extern u16           D_8014638A;
/* The selected battler's row (D_8014638C), stored by func_801D3624. */
extern PartyBattler* g_BattleSelectedActor;
extern void*         D_80146390;
extern s32           D_8014639C;
extern u16           D_801463B2;
extern u8            D_801463B9;
/* D_801463C0 */
extern volatile u16  g_BattleActionId;
extern u16           D_801463C2;
extern u8            D_801463C8;
/* The slot that owns the pending panel: battle/battle/15 latches the selected slot
 * into it (func_8009FAE4), battle/battle/03 clears the 0x4000 event bit when the
 * active row's slot matches it (Battle_DefeatEnemy). */
extern u8            D_801463CA;
extern u8            D_801463CD;
extern u8            D_801463CF;
extern u8            D_801463D4;
extern u8            D_801463D5;
extern u8            D_801463D7;
extern u8            D_80148450;
extern u8            D_8014845A;
extern u8            D_80148474;
extern u8            D_80148498;
extern u8            D_801484BC;
extern u8            D_801484E0;
extern u16           D_801485A4;
extern s16           D_801485D6;
/* D_801EAF3C */
extern volatile u16  g_BattleTurnPriorityMultipliers[6];
/* D_801EAF88 */
extern volatile u8   g_BattleLevelThresholds[12];
/* Enemy battler record base for both battle overlays. */
/* D_801EB2E8 */
extern u8            g_BattleEnemies[];
/* The active battle work row, the pointer battle/battle/03 and the bmagic
 * overlays advance through the effect steps. It is a non-volatile view on
 * purpose: some retail stores rely on the plain form, for example the counter
 * store in the return-jump delay slot of func_801E8D04. */
extern PartyBattler* D_801EB4E0;
/* The current battler's enemy work row (the row at ENEMY_COMBATANT_BASE that
 * the battle mode is running). battle/battle/03 stores it when it arms a slot
 * (func_801E2170) and battle/battle/15 reads its cells (Battle_TestAICondition). */
/* D_801EB4E8 */
extern EnemyBattler* g_BattleCurrentEnemy;
extern u8            D_801EB6B2[];
/* Enemy battler work record (stride 0x118, indexed by slot - 3). */
extern EnemyBattler  g_BattleEnemyBattlers[];

#endif
