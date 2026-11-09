#ifndef SCENARIO_FAMILY_H
#define SCENARIO_FAMILY_H

/* Declarations shared by two or more scenario images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "sys/scene.h"
#include "gfx/prim.h"
#include "area/map.h"
#include "sys/actor.h"
#include "scenario/effect.h"
#include "scenario/overlay.h"
#include "scenario/runtime.h"
#include "sys/cd.h"

s8 func_801A7AD8(u8* entry, u8 count, u16 x, u16 y);

/* The body of a scene's position probe: look the position up in a table of `count` entries and run
 * the handler at the index found, returning its result, else -1. The probes differ only in table,
 * count and handlers. Every change here must verify every member. */
#define SCENE_PROBE_POSITION(table, count, handlers)          \
    do {                                                      \
        s8 index;                                             \
                                                              \
        index = func_801A7AD8(&(table), (count), x, y);       \
        if (index < 0) {                                      \
            return -1;                                        \
        }                                                     \
        return (handlers)[index]();                           \
    } while (0)

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

    actor              = SP_REF(Actor*, 0x44);
    actor->header.step = (u8)(actor->header.step + 1);
}

/* Advance the current actor's step index. */
static inline void Scene_AdvanceActorStep(void) {
    Actor* actor;

    actor              = SP_REF(Actor*, 0x44);
    actor->header.mode = (u8)(actor->header.mode + 1);
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

s16  func_801F326C(s32 message);
s16  func_801F37AC(s32 message);
void func_801F7484(void);
void func_801F74EC(void);
void func_801F7A18(void);
void Scene_ClearParty(void);
void Scene_ClearScanBars(void);
void Area_ClearWorkColumn(void);
void GFX_DrawShadedDisc(s16 x, s16 y, s16 radius, u8 center_shade, u8 rim_shade);

/* Scene dispatch table indexed by the mode byte at D_80146872. */
extern s8 D_80146872;
#endif
