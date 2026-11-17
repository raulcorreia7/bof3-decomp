#ifndef OVERLAY_SCENARIO_SCENA08_00_H
#define OVERLAY_SCENARIO_SCENA08_00_H

/* The scenario/scena08/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"
#include "area/spad.h"
#include "overlays/area/AreaSprite.h"
#define SCRATCH_ROW_STRIDE 0x28
#define SCRATCH_ROW_OFFSET 0x00

extern u16      D_800E4C1E;
extern s16      D_801448EE;
extern u8       D_80144EC8[];
extern u8       D_80145FD0;
extern u16      D_80146258;
extern u8       D_80146921;
extern u8       D_80146997;
extern s8       D_80147ACF;
extern s16      D_80147AD6;
extern u32      D_801F6C00;
/* D_801FE894 */
extern Callback D_801FE8A0[];
extern Callback D_801FE8D0[];
extern Callback D_801FE8D8[];
extern Callback D_801FE8E4[];

/* A billboard row of the sprite work table: the world point it stands on, its shade and its size word. */
typedef struct Scena08Billboard {
    u8     unk_00[3];    /* +0x00 */
    u8     shade;        /* +0x03 */
    VECTOR pos;          /* +0x04 */
    u8     unk_14[0x10]; /* +0x14 */
    u32    size;         /* +0x24 */
} Scena08Billboard;

ASSERT_OFFSET(Scena08Billboard, size, 0x24);
ASSERT_SIZE(Scena08Billboard, 0x28);

/* The SCENA08_SPARK_COUNT falling sparks at AREA_WORK; FallingSpark is in scenario.h. */
#define SCENA08_SPARK_COUNT 8U

extern void (*D_801FE8FC[])(FallingSpark* spark);

void          func_801F7DE8(void);
s32           func_801F7E14(void);
void          func_801F8AE8(void);
u8            func_801F8BF8(void);
FallingSpark* func_801F8B14(void);
void          Scene_InitSpark(FallingSpark* spark);
void          func_801F81F4(u16 value);
void          func_801F823C(s16 x, s16 y, s16 half_height, s16 half_width);

void func_801F9688(void);

extern Callback jtbl_801F6C8C[11];
extern Callback jtbl_801F6CE4[16];
extern Callback D_801FE908[];
extern Callback D_801FE910[];

extern Callback D_801FE938[];
extern Callback D_801FE964[];
extern Callback D_801FE970[];
extern u8       D_801FE9A0[];
/* D_801FE9C0 */
extern u16      D_801FE9EC[];
extern u8       D_801FEA6C;
extern u8       D_801FEA70;
extern s32      D_801FEA74;
extern s32      D_801FEA78;

void func_801FE800(void);

void func_801F8964(FallingSpark* spark);
/* func_801F8D98 */
void MotionTrail_Update(void* table);

void func_801F90C8(void* table);
void func_801FA32C(void);
void func_801FE12C(void);

void func_801FA19C(WorldPos* pos, s32* vx);

void func_801F9F8C(WorldPos* pos, s32 unused, s32 jitter, s32 layer);

void func_801F85F0(s16 x, s16 y, s16 radius);
void func_801F8108(s32 x, s32 y);

/* The two screen-effect steps of 348.c: draw at the actor's screen position, turn it by `step`, and leave the scene when the countdown ends. They differ only in the sign of the turn. */
#define SCENA08_SCREEN_EFFECT_STEP(work, step)                                        \
    func_801F85F0((s16)g_Task->screen_x, (s16)g_Task->screen_y, (s16)g_Task->unk_32); \
    (work) = g_Task;                                                                  \
    (work)->unk_32 += (step);                                                         \
    if (--(work)->unk_5A == 0) {                                                      \
        func_80196070();                                                              \
    }

/* The two sparkle steps of 348.c: stir the seed, advance the frame counters and move to the next mode after `reset` frames. They differ only in `reset`. */
#define SCENA08_SPARKLE_STEP(count, timer, reset) \
    func_801F8534();                              \
    g_Task->script_pc += RANDOM_MASK(BYTE_MASK);  \
    if ((g_Task->unk_5A & 3) == 0) {              \
        g_Task->unk_2C += 1;                      \
    }                                             \
    (count)        = g_Task->unk_32 + 1;          \
    (timer)        = g_Task->unk_5A - 1;          \
    g_Task->unk_5A = (timer);                     \
    g_Task->unk_32 = (count);                     \
    if ((timer) == 0) {                           \
        g_Task->unk_5A = (reset);                 \
        g_Task->header.mode += 1;                 \
    }

/* The two sparkle starts of 348.c: seed the frame counters, stir the seed 0x40 times and play `cue`. They differ only in `cue`. */
#define SCENA08_SPARKLE_START(i, cue)                \
    g_Task->unk_5A    = 0x20;                        \
    g_Task->unk_32    = 0;                           \
    g_Task->script_pc = 0;                           \
    for ((i) = 0; (i) < 0x40; (i)++) {               \
        g_Task->script_pc += RANDOM_MASK(BYTE_MASK); \
        func_801F81F4(g_Task->script_pc);            \
    }                                                \
    g_Task->unk_2C = 0;                              \
    SND_PlaySE(cue);                                 \
    g_Task->header.mode += 1;

#endif
