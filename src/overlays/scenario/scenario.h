#ifndef SCENARIO_FAMILY_H
#define SCENARIO_FAMILY_H

/* Declarations shared by two or more scenario images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "sys/scene.h"
#include "gfx/prim.h"
#include "area/map.h"
#include "work/actor.h"
#include "scenario/effect.h"
#include "scenario/overlay.h"
#include "scenario/runtime.h"
#include "sys/cd.h"

#define SCRATCH_COLUMN_COUNT  0x80
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_STRIDE 0x14
#define SCAN_BAR_COUNT        16

typedef struct ScanBar {
    /* 0x00 */ u8  in_use;
    /* 0x01 */ u8  unk_01;
    /* 0x02 */ u8  state;
    /* 0x03 */ u8  half_height;
    /* 0x04 */ s16 y;
} ScanBar;

ASSERT_SIZE(ScanBar, 6);
ASSERT_OFFSET(ScanBar, in_use, 0x00);
ASSERT_OFFSET(ScanBar, state, 0x02);
ASSERT_OFFSET(ScanBar, half_height, 0x03);
ASSERT_OFFSET(ScanBar, y, 0x04);

/* The scene context record the entity dispatchers pass to their handler. */
#define g_SceneFlags ((void*)g_SceneFlags)

/* Advance the current actor's state byte. */
static inline void Scene_AdvanceActorState(void) {
    Actor* actor;

    actor           = SP_REF(Actor*, 0x44);
    actor->state_02 = (u8)(actor->state_02 + 1);
}

/* Advance the current actor's step index. */
static inline void Scene_AdvanceActorStep(void) {
    Actor* actor;

    actor         = SP_REF(Actor*, 0x44);
    actor->unk_01 = (u8)(actor->unk_01 + 1);
}

/* The scenario request cell: the step machine stores and steps it as a byte,
 * while the frontend reset clears the whole word. */
typedef union SceneRequest {
    u32 word;
    u8  byte;
} SceneRequest;

ASSERT_SIZE(SceneRequest, 4);
ASSERT_OFFSET(SceneRequest, word, 0x00);
ASSERT_OFFSET(SceneRequest, byte, 0x00);

#define g_ScriptVarsReq (*(SceneRequest*)&g_ScriptVars)

void func_801F7484(void);
void func_801F74EC(void);
void func_801F7A18(void);
/* func_801FC8FC */
void Scene_ClearParty(void);

/* Scene dispatch table indexed by the mode byte at D_80146872. */
extern s8 D_80146872;
#endif
