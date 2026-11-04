#ifndef WORK_STATE_H
#define WORK_STATE_H

#include "types.h"

/* Copied whole from the save image 0x801448D8 by etc/start/08 SAVE_RunLoadRestore.
 * scenario_id selects the overlay and its handler table (func_801A782C); flags_01
 * bit 0x80 and 0x20 are set by Scene_RequestChapterAdvance and func_8019A904; mode_02 is the
 * dispatch byte of every scenario overlay (scena09 764.c); step_05 is the step
 * each controller switches on (scena00 8.c); timer_06 counts that step down. */
typedef struct SceneState {
    s8  scenario_id;
    u8  flags_01;
    u8  mode_02;
    u8  unk_03;
    s8  state_04;
    u8  step_05;
    u16 timer_06;
    u16 unk_08;
    u8  pad_0A[6]; /* the copy is 0x10 bytes; these six bytes have no reader */
} SceneState;

ASSERT_SIZE(SceneState, 0x10);
ASSERT_OFFSET(SceneState, flags_01, 0x01);
ASSERT_OFFSET(SceneState, mode_02, 0x02);
ASSERT_OFFSET(SceneState, state_04, 0x04);
ASSERT_OFFSET(SceneState, step_05, 0x05);
ASSERT_OFFSET(SceneState, timer_06, 0x06);

typedef union GameStateCounter {
    s8 s8_value;
    u8 u8_value;
} GameStateCounter;

typedef struct GameStateRecord {
    /* 0x00 */ u8                pad_00[0x79];
    /* 0x79 */ u8                slot_index_79; /* active slot index */
    /* 0x7A */ u8                pad_7A[0x9E];
    /* 0x118 */ u8               flags_118;     /* bit 0x80 restores the saved word */
    /* 0x119 */ u8               countdown_119; /* frame countdown, reloaded with 0x28 or 0x0A */
    /* 0x11A */ u8               pad_11A[0x2];
    /* 0x11C */ GameStateCounter counter_11C; /* panel step counter */
    /* 0x11D */ u8               pad_11D[0x1];
    /* 0x11E */ u8               kind_11E;  /* record kind */
    /* 0x11F */ u8               wait_11F;  /* shared wait countdown */
    /* 0x120 */ u16              value_120; /* copied into the record's 0x7C */
    /* 0x122 */ u16              unk_122;   /* lowered by 2 per step; @source: write:func_801F3B9C@0x801F3B9C */
    /* 0x124 */ u32              index_124; /* slot index passed to the selector */
    /* 0x128 */ u8               pad_128[0x2];
    /* 0x12A */ GameStateCounter step_12A;
    /* 0x12B */ GameStateCounter mode_12B;  /* panel mode */
    /* 0x12C */ GameStateCounter flags_12C; /* bit 0x01/0x08 gate the entry check */
    /* 0x12D */ u8               slot_12D;  /* entity slot index */
    /* 0x12E */ u8               pad_12E[0xE];
    /* 0x13C */ u8               slot_13C; /* ability record index */
    /* 0x13D */ u8               unk_13D;  /* the palette fade index; @source: write:func_801AAB00@0x801AAB00 */
} GameStateRecord;

ASSERT_SIZE(GameStateRecord, 0x140);
ASSERT_OFFSET(GameStateRecord, slot_index_79, 0x79);
ASSERT_OFFSET(GameStateRecord, flags_118, 0x118);
ASSERT_OFFSET(GameStateRecord, countdown_119, 0x119);
ASSERT_OFFSET(GameStateRecord, counter_11C, 0x11C);
ASSERT_OFFSET(GameStateRecord, kind_11E, 0x11E);
ASSERT_OFFSET(GameStateRecord, wait_11F, 0x11F);
ASSERT_OFFSET(GameStateRecord, value_120, 0x120);
ASSERT_OFFSET(GameStateRecord, unk_122, 0x122);
ASSERT_OFFSET(GameStateRecord, index_124, 0x124);
ASSERT_OFFSET(GameStateRecord, step_12A, 0x12A);
ASSERT_OFFSET(GameStateRecord, mode_12B, 0x12B);
ASSERT_OFFSET(GameStateRecord, flags_12C, 0x12C);
ASSERT_OFFSET(GameStateRecord, slot_12D, 0x12D);
ASSERT_OFFSET(GameStateRecord, slot_13C, 0x13C);
ASSERT_OFFSET(GameStateRecord, unk_13D, 0x13D);

/* The mode and flag bytes (GameStateRecord +0x12B and +0x12C) of each mode work
 * record, addressed from the first record's mode byte at a 0x140 stride. */
typedef struct AreaPartyMode {
    u8 mode;
    u8 flags;
    u8 pad_02[0x13E];
} AreaPartyMode;

ASSERT_SIZE(AreaPartyMode, 0x140);

/* The current mode work record; battle points it at a g_BattlePartyBattlers row. */
/* D_80146250 */
extern GameStateRecord* g_GameState; /* 0x80146250 */
/* D_80145FBB */
extern AreaPartyMode    D_80145FBB[]; /* 0x80145FBB */
/* The scenario record the overlays switch on. */
/* D_80146870 */
extern SceneState       g_SceneState; /* 0x80146870 */

#endif
