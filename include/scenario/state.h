#ifndef SCENARIO_STATE_H
#define SCENARIO_STATE_H

#include "battle/records.h"
#include "types.h"

/* Copied whole from the save image 0x801448D8 by etc/start/08 SAVE_RunLoadRestore.
 * scenario_id selects the overlay and its handler table (func_801A782C); flags_01
 * bit 0x80 and 0x20 are set by Scene_RequestChapterAdvance and func_8019A904; mode_02 is the
 * dispatch byte of every scenario overlay (scena09 764.c); step_05 is the step
 * each controller switches on (scena00 8.c); timer_06 counts that step down. */
/* g_SceneState.flags_01. Bit 0x01 is read by the script kind 9 and by the Ryu pajama intro checks; its role is
 * not named. */
typedef enum SceneStateFlags {
    SCENE_STATE_CAMERA_MOVING = 1
        << 5, /* set when a camera move starts, cleared when it ends (func_8019A904, func_8019AAFC) */
    SCENE_STATE_SCRIPT_ACTIVE   = 1 << 6, /* set with GAME_FLAG_SCRIPT_ACTIVE by Game_SetScriptActive */
    SCENE_STATE_CHAPTER_ADVANCE = 1 << 7, /* set by Scene_RequestChapterAdvance; func_8019FAA0 steps the scenario */
} SceneStateFlags;

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

/* The scenario record the overlays switch on. */
/* D_80146870 */
extern SceneState g_SceneState; /* 0x80146870 */
/* state_04 and step_05 as one halfword (step in the high byte); area085 and
 * area105 compare the pair with one lhu. */
#define SCENE_PROGRESS (*(u16*)&g_SceneState.state_04)

#endif
