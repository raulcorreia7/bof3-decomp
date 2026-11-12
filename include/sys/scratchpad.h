#ifndef SYSTEM_SCRATCHPAD_H
#define SYSTEM_SCRATCHPAD_H

/* Every overlay lands its own work pointer in the cell at 0x1F800044, so each view types that cell with the
 * mode's work-area tag. The tags are incomplete here and are completed by the target that owns them:
 * battle/battle/03 and battle/battle/15 (struct PartyMember), the area overlays (struct Actor,
 * sys/actor.h), the scenario overlays (struct SceneBandEffect) and the commu overlays (struct
 * CommunicationTaskSlot). Area code reads the cell through area/spad.h; the area view below only
 * types the pointer cell itself.
 *
 * Volatility is a per-access property, not part of the layout: code that must reload the cell on every
 * evaluation keeps its volatile spelling; the views below are the non-volatile layout. */

#include "psx/mem.h"
#include "psx/psyq.h"
#include "types.h"

/* Four SVECTORs at 0x14. The scenario overlay indexes them as the argument vector for RotTransPers4
 * (func_801D165C) and the common executable stores halfword coordinates at 0x1C-0x30. */
typedef struct ScratchPadVector {
    u8      pad_00[0x14];
    SVECTOR vectors[4]; /* 0x14 */
} ScratchPadVector;

#define SCRATCH_PAD_VECTOR_VIEW_SIZE 0x34
ASSERT_SIZE(ScratchPadVector, SCRATCH_PAD_VECTOR_VIEW_SIZE);
ASSERT_OFFSET(ScratchPadVector, vectors, 0x14);

/* Battle overlays: bytes 0-2 stage the current local-work byte 9 (func_801E6A54), byte 0 advances the
 * slot index (written by func_801DE43C, read by func_801DE754). Byte 0x03 has no battle access yet. */
typedef struct ScratchPadBattle {
    u8                  state_00;     /* 0x00 */
    u8                  state_01;     /* 0x01 */
    u8                  state_02;     /* 0x02 */
    u8                  pad_03[0x41]; /* 0x03 */
    struct PartyMember* work_ptr;     /* 0x44 */
} ScratchPadBattle;

#define SCRATCH_PAD_BATTLE_VIEW_SIZE 0x48
ASSERT_SIZE(ScratchPadBattle, SCRATCH_PAD_BATTLE_VIEW_SIZE);
ASSERT_OFFSET(ScratchPadBattle, state_00, 0x00);
ASSERT_OFFSET(ScratchPadBattle, state_01, 0x01);
ASSERT_OFFSET(ScratchPadBattle, state_02, 0x02);
ASSERT_OFFSET(ScratchPadBattle, work_ptr, 0x44);

/* Field overlays: the entity counter and entry-data halves at 0x00 (GAME_ENTITY_COUNTER,
 * GAME_ENTITY_ENTRY_DATA in emi/etc/game/00) and the work-area pointer at 0x44. */
typedef struct ScratchPadArea {
    s16           entity_counter; /* 0x00 */
    u16           entry_data;     /* 0x02 */
    u8            pad_04[0x40];   /* 0x04 */
    struct Actor* work_ptr;       /* 0x44 */
} ScratchPadArea;

#define SCRATCH_PAD_AREA_VIEW_SIZE 0x48
ASSERT_SIZE(ScratchPadArea, SCRATCH_PAD_AREA_VIEW_SIZE);
ASSERT_OFFSET(ScratchPadArea, entity_counter, 0x00);
ASSERT_OFFSET(ScratchPadArea, entry_data, 0x02);
ASSERT_OFFSET(ScratchPadArea, work_ptr, 0x44);

/* Scene overlays: four scratch math words (D_1F800000/4/8/C), the volatile halfword-pointer cell
 * (s16 *volatile D_1F800010 in scna00/00) and the RotTransPers4 vector block at 0x14. */
typedef struct ScratchPadScenario {
    s32 math_00;                           /* 0x00 */
    s32 math_04;                           /* 0x04 */
    s32 math_08;                           /* 0x08 */
    s32 math_0C;                           /* 0x0C */
    s16* volatile data_ptr_10;             /* 0x10 */
    SVECTOR                 vectors_14[4]; /* 0x14 */
    u8                      pad_34[0x10];  /* 0x34 */
    struct SceneBandEffect* work_ptr;      /* 0x44 */
} ScratchPadScenario;

#define SCRATCH_PAD_SCENARIO_VIEW_SIZE 0x48
ASSERT_SIZE(ScratchPadScenario, SCRATCH_PAD_SCENARIO_VIEW_SIZE);
ASSERT_OFFSET(ScratchPadScenario, math_00, 0x00);
ASSERT_OFFSET(ScratchPadScenario, math_04, 0x04);
ASSERT_OFFSET(ScratchPadScenario, math_08, 0x08);
ASSERT_OFFSET(ScratchPadScenario, math_0C, 0x0C);
ASSERT_OFFSET(ScratchPadScenario, data_ptr_10, 0x10);
ASSERT_OFFSET(ScratchPadScenario, vectors_14, 0x14);
ASSERT_OFFSET(ScratchPadScenario, work_ptr, 0x44);

/* Battle effect draw routines (the bmagic rings): halfword parameters at 0x00, such as the ring radii and
 * edge shades, ahead of the RotTransPers4 corner vectors at 0x14 (D_1F800014). */
typedef struct ScratchPadEffect {
    s16     params[10]; /* 0x00 */
    SVECTOR vectors[4]; /* 0x14 */
} ScratchPadEffect;

#define SCRATCH_PAD_EFFECT_VIEW_SIZE 0x34
ASSERT_SIZE(ScratchPadEffect, SCRATCH_PAD_EFFECT_VIEW_SIZE);
ASSERT_OFFSET(ScratchPadEffect, vectors, 0x14);

/* The sparkle ray cells at 0x00: the sparkle's screen point (0x00, 0x02), the sweep angle (0x06) and
 * the RGB shade the rays fade to (0x08, 0x0A, 0x0C). */
typedef struct ScratchPadRay {
    u16 x; /* 0x00 */
    u16 y; /* 0x02 */
    u8  pad_04[2];
    s16 angle; /* 0x06 */
    u16 red;   /* 0x08 */
    u16 green; /* 0x0A */
    u16 blue;  /* 0x0C */
} ScratchPadRay;

#define SCRATCH_PAD_RAY_VIEW_SIZE 0x0E
ASSERT_SIZE(ScratchPadRay, SCRATCH_PAD_RAY_VIEW_SIZE);
ASSERT_OFFSET(ScratchPadRay, angle, 0x06);
ASSERT_OFFSET(ScratchPadRay, red, 0x08);
ASSERT_OFFSET(ScratchPadRay, blue, 0x0C);

/* The scratchpad seen as one object: the raw byte view the loader streams through, plus one member per
 * mode. The views are prefixes (0x48 or less); the raw view is the full 1 KiB. */
typedef union ScratchPadViews {
    u8                 raw[SCRATCH_PAD_SIZE]; /* 0x000 */
    ScratchPadBattle   battle;                /* 0x000 */
    ScratchPadArea     area;                  /* 0x000 */
    ScratchPadScenario scenario;              /* 0x000 */
    ScratchPadVector   vector;                /* 0x000 */
    ScratchPadEffect   effect;                /* 0x000 */
    ScratchPadRay      ray;                   /* 0x000 */
} ScratchPadViews;

ASSERT_SIZE(ScratchPadViews, SCRATCH_PAD_SIZE);

typedef struct ScratchPad {
    ScratchPadViews view; /* 0x000 */
} ScratchPad;

ASSERT_SIZE(ScratchPad, SCRATCH_PAD_SIZE);
ASSERT_OFFSET(ScratchPad, view, 0x000);

/* The scratchpad as a typed object at a byte offset: SPAD(0u)->view.battle.state_00. The existing
 * SCRATCH_PAD/SP/SP_PTR/SP_REF helpers in psx/mem.h keep working; prefer a view member once the mode
 * and offset are both known. */
#define SPAD(byte_offset) SP_PTR(ScratchPad, byte_offset)

/* Scratchpad base + 1; battle/battle/03 and etc/game/00 write it directly. */
extern u8  D_1F800001;
/* The staged y coordinate that func_801B13BC writes, and the phase angle the KaiserBreath steps
 * store before rcos loads it back. */
extern s16 D_1F800006;
extern s16 D_1F800034[2];
/* The area emit slots: the pair extent and its mode. */
extern s16 D_1F800038;
extern s16 D_1F80003A;

#endif
