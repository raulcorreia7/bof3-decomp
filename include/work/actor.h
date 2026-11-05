#ifndef WORK_ACTOR_H
#define WORK_ACTOR_H

/* The field actor table at 0x80146888: 30 rows of 0x98 bytes, one per map
 * object or interaction slot in the current area. Every overlay reads the same
 * rows: the area overlays walk them to place objects and run their scripts, the
 * communication minigame indexes them as tasks, the scenario overlays dispatch
 * their callbacks, and the fishing code steps the stamina gauge of the pond
 * rows. The scratchpad work cell at 0x1F800044 points into the table and the
 * pointer cell g_CurrentActor publishes the current row.
 *
 * The community map names the table the fish pond array
 * (tasks/names-ram/ram-map.tsv); the readers reject that: only emi/world00/
 * area030/04 reads it as a pond, every other overlay reads the same rows as map
 * objects, tasks or scenario entities.
 *
 * Retail loads one offset at several widths and signs (a signed byte at +0x5D is
 * `lb`, an unsigned one `lbu`). A member keeps the width its most frequent
 * reader uses; a unit whose bytes need the other width casts the member and
 * carries a FAKE comment. */

#include "common/vector.h"
#include "types.h"

/* The record's size, its stride in the table and the table's row count. */
#define ACTOR_SIZE           0x98
#define ACTOR_COUNT          30

/* Ask whether a work row is live: the update walks only rows with the in-use
 * bit set. Pass the row itself or, for a pointer, its dereference. */
#define ACTOR_IN_USE(actor)  (((actor).flags_00 & ACTOR_FLAG_IN_USE) != 0)

/* The actor's state step in the scratchpad work cell: the byte
 * SYS_DISPATCH_TASK indexes and the battle step tables read and write. */
#define ACTOR_SET_STEP(step) (g_SpadWork[1] = (step))

/* Clear the actor's state step: the record starts a new task at state 0. */
#define ACTOR_CLEAR_STATE()  (g_SpadWork->state_02 = 0)

/* `flags_00` bits. Bit 0 marks a row the update walks; bit 1 skips queuing the
 * row's palette pair; bit 4 takes the advance-stream tail after the step
 * deltas; bit 5 makes the row's primitives semi-transparent; bit 6 hides the
 * row from the draw, walkability and entity-lookup paths; bit 7 marks a row
 * culled outside the window. */
typedef enum ActorFlags {
    ACTOR_FLAG_IN_USE             = 1 << 0,
    ACTOR_FLAG_SKIP_PALETTE_STAGE = 1 << 1,
    ACTOR_FLAG_STEP_MOVE          = 1 << 4,
    ACTOR_FLAG_SEMI_TRANSPARENT   = 1 << 5,
    ACTOR_FLAG_HIDDEN             = 1 << 6,
    ACTOR_FLAG_OFFSCREEN          = 1 << 7,
} ActorFlags;

/* `flags_24` bit 6 marks the record active. */
typedef enum ActorActiveFlags {
    ACTOR_FLAG_ACTIVE = 1 << 6,
} ActorActiveFlags;

/* `flags_74` bits. Bit 0 runs the area interaction handler; bits 1 and 2 select
 * the white and black fade handlers; bit 3 marks a path or movement step in
 * progress (set when a move starts, cleared on arrival); bit 4 starts the
 * map/message request; bit 5 dispatches the scenario record. */
typedef enum ActorInteractionFlags {
    ACTOR_FLAG_INTERACTION_PENDING = 1 << 0,
    ACTOR_FLAG_FADE_WHITE          = 1 << 1,
    ACTOR_FLAG_FADE_BLACK          = 1 << 2,
    ACTOR_FLAG_MOVING              = 1 << 3,
    ACTOR_FLAG_SCRIPT_REQUEST      = 1 << 4,
    ACTOR_FLAG_SCRIPT_PENDING      = 1 << 5,
} ActorInteractionFlags;

/* `option_flags`, the spawn record's option byte. Bit 0 hides the row at spawn; bit 1
 * keeps its own route instead of the opposite facing; bit 2 drops the script
 * arm; bit 3 skips re-applying the route; bit 5 skips the animation-stream
 * advance; bit 7 skips the walkability/target test and entity lookup. */
typedef enum ActorOptionFlags {
    ACTOR_OPT_HIDDEN_ON_SPAWN = 1 << 0,
    ACTOR_OPT_KEEP_FACING     = 1 << 1,
    ACTOR_OPT_NO_SCRIPT_START = 1 << 2,
    ACTOR_OPT_ROUTE_LOCKED    = 1 << 3,
    ACTOR_OPT_WAIT_STREAM     = 1 << 5,
    ACTOR_OPT_NO_TARGET       = 1 << 7,
} ActorOptionFlags;

/* The word at +0x54: the range table pointer, or the same word copied as an
 * integer. */
typedef union ActorRange {
    s8* table;
    u32 word;
} ActorRange;

ASSERT_SIZE(ActorRange, 0x04);

/* The word at +0x5C: a flags byte then three tint bytes. The scene code reads
 * it whole to compare a packed tint, as unsigned bytes, and as the signed steps
 * the fade adds toward 0xC0 (emi/world00/area032/13 marker_work.c). */
typedef union ActorTint {
    s32 word;

    struct {
        u8 flags;
        u8 unk_5D;
        u8 unk_5E;
        u8 unk_5F;
    } bytes;

    struct {
        s8 flags;
        s8 unk_5D;
        s8 unk_5E;
        s8 unk_5F;
    } signed_bytes;

    struct {
        u16 unk_5C;
        u16 unk_5E;
    } halves;
} ActorTint;

ASSERT_SIZE(ActorTint, 0x04);

/* The word at +0x70: the scene flag-table byte alone, or the whole word. The word
 * packs voice numbers above the byte (SND_QueueSelectionFx ORs them in,
 * Area_FindSceneRecord masks and loads it); area code clears it or passes it
 * whole as the range mode of func_801BE0C0. */
typedef union ActorStateWord {
    u32 word;
    u8  byte;
} ActorStateWord;

ASSERT_SIZE(ActorStateWord, 0x04);

typedef struct Actor {
    u8             flags_00;       /* 0x00 - entity flags; ActorFlags */
    u8             unk_01;         /* 0x01 - commu00 calls it the task mode */
    u8             state_02;       /* 0x02 - commu00 calls it the task state */
    u8             unk_03;         /* 0x03 */
    u8             unk_04;         /* 0x04 */
    u8             unk_05;         /* 0x05 - region/scene index; commu00 calls it the
                                *        source row the task came from; the script copy
                                *        scales its staging offset by it; cleared at scene init */
    u8             unk_06;         /* 0x06 - commu00 calls it the live flag; 9 gates the draw-mode
                                *        stamp, 10 calls func_8015A944 (func_80167E00) */
    u8             option_flags;   /* 0x07 - ActorOptionFlags */
    u8             direction_08;   /* 0x08 - commu00 calls it the cue resource */
    u8             unk_09;         /* 0x09 - area032 calls it the marker mode byte */
    u8             unk_0A;         /* 0x0A */
    u8             unk_0B;         /* 0x0B */
    s32            unk_0C;         /* 0x0C - area032 adds it to x as the x step */
    s32            unk_10;         /* 0x10 */
    s32            vz;             /* 0x14 signed vertical speed */
    s32            unk_18;         /* 0x18 - commu00 calls it variant_arg_0 */
    s32            unk_1C;         /* 0x1C - commu00 calls it variant_arg_1 */
    s32            gravity;        /* 0x20 added to vz each step */
    u8             flags_24;       /* 0x24 - ActorActiveFlags; bit 0x40 marks the record active */
    u8             unk_25;         /* 0x25 */
    u8             unk_26;         /* 0x26 */
    u8             unk_27;         /* 0x27 */
    u8             unk_28;         /* 0x28 */
    u8             unk_29;         /* 0x29 */
    u8             unk_2A;         /* 0x2A */
    u8             unk_2B;         /* 0x2B */
    u16            unk_2C;         /* 0x2C */
    u16            unk_2E;         /* 0x2E - area032 calls it the marker's screen x */
    u16            unk_30;         /* 0x30 - area032 calls it the marker's screen y */
    u16            unk_32;         /* 0x32 */
    Coord          x;              /* 0x34 */
    Coord          y;              /* 0x38 */
    Coord          z;              /* 0x3C - the integer half (+2) is the ground height */
    s32            unk_40;         /* 0x40 */
    s32            unk_44;         /* 0x44 */
    u8             unk_48;         /* 0x48 - commu00 calls it the reset flag */
    u8             unk_49;         /* 0x49 */
    u8             unk_4A;         /* 0x4A - the world slot mode seed */
    u8             unk_4B;         /* 0x4B - the script-bank record index */
    s32            unk_4C;         /* 0x4C */
    u8*            source_50;      /* 0x50 - cursor into the area script stream (Actor_CopyScriptEntry,
                                *        Actor_SeekScript) */
    ActorRange     range_54;       /* 0x54 - range record; +2 range, +3 bit 0x10 */
    u16            script_pc;      /* 0x58 - byte position in the script stream at source_50 */
    u16            unk_5A;         /* 0x5A */
    ActorTint      tint;           /* 0x5C */
    s32            unk_60;         /* 0x60 */
    s32            unk_64;         /* 0x64 */
    s32            unk_68;         /* 0x68 */
    s32            unk_6C;         /* 0x6C */
    ActorStateWord state_70;       /* 0x70 - see ActorStateWord */
    u8             flags_74;       /* 0x74 - ActorInteractionFlags */
    u8             timer_75;       /* 0x75 */
    u8             pad_76;         /* 0x76 */
    u8             unk_77;         /* 0x77 */
    u8             unk_78;         /* 0x78 - commu00 names this variant_state, area008 its
                                *        state_78 */
    u8             unk_79;         /* 0x79 */
    u8             callback_index; /* 0x7A - index of the scenario callback table; 0xFF is none */
    u8             unk_7B;         /* 0x7B */
    u16            unk_7C;         /* 0x7C - 16-bit signal; commu00 calls it the label id */
    u16            unk_7E;         /* 0x7E */
    s32            unk_80;         /* 0x80 */
    s32            unk_84;         /* 0x84 */
    u32            unk_88;         /* 0x88 */
    s16            stamina_max_8C; /* 0x8C */
    u16            stamina_8E;     /* 0x8E - the fishing gauge: a signed delta is added and
                                *        the result is clamped into [0, +0x8C]
                                *        (emi/world00/area030/04 func_801E026C) */
    u16            roll_90;        /* 0x90 */
    u8             facing_92;      /* 0x92 - the facing direction: the fishing code writes
                                *        `rand() & 3` and turns the row by it
                                *        (emi/world00/area030/04 func_801DE5EC) */
    u8             unk_93;         /* 0x93 */
    u8             unk_94;         /* 0x94 */
    u8             unk_95;         /* 0x95 */
    u8             pad_96[0x02];   /* 0x96-0x97 */
} Actor;

ASSERT_SIZE(Actor, ACTOR_SIZE);
ASSERT_OFFSET(Actor, flags_00, 0x00);
ASSERT_OFFSET(Actor, direction_08, 0x08);
ASSERT_OFFSET(Actor, vz, 0x14);
ASSERT_OFFSET(Actor, unk_18, 0x18);
ASSERT_OFFSET(Actor, gravity, 0x20);
ASSERT_OFFSET(Actor, flags_24, 0x24);
ASSERT_OFFSET(Actor, x, 0x34);
ASSERT_OFFSET(Actor, y, 0x38);
ASSERT_OFFSET(Actor, z, 0x3C);
ASSERT_OFFSET(Actor, range_54, 0x54);
ASSERT_OFFSET(Actor, tint, 0x5C);
ASSERT_OFFSET(Actor, state_70, 0x70);
ASSERT_OFFSET(Actor, flags_74, 0x74);
ASSERT_OFFSET(Actor, unk_77, 0x77);
ASSERT_OFFSET(Actor, callback_index, 0x7A);
ASSERT_OFFSET(Actor, unk_7C, 0x7C);
ASSERT_OFFSET(Actor, unk_88, 0x88);
ASSERT_OFFSET(Actor, stamina_8E, 0x8E);
ASSERT_OFFSET(Actor, facing_92, 0x92);

/* D_80146884 */
extern Actor* g_CurrentActor; /* 0x80146884 */
extern Actor  g_Actors[ACTOR_COUNT];

#endif
