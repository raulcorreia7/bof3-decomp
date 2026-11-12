#ifndef OVERLAY_SCENARIO_SCENA08_00_H
#define OVERLAY_SCENARIO_SCENA08_00_H

/* The scenario/scena08/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"
#include "overlays/area/AreaSprite.h"
#define SCRATCH_ROW_STRIDE 0x28
#define SCRATCH_ROW_OFFSET 0x00

extern u16      D_800E4C1E;
extern u8       D_80144EC8[];
extern u8       g_VitalItemIds;
extern s16      D_801448EE;
extern u8       D_80146867;
extern s8       D_80147ACF;
extern s16      D_80147AD6;
extern u8       D_80146874;
extern u8       D_80146875;
extern u16      D_80146876;
extern u32      D_801F6C00;
/* D_801FE894 */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801FE8A0[];
extern Callback D_801FE8D0[];
extern Callback D_801FE8D8[];
extern Callback D_801FE8E4[];

/* One of the SCENA08_SPARK_COUNT falling sparks at AREA_WORK: kind selects the per-frame handler in D_801FE8FC. */
#define SCENA08_SPARK_COUNT 8U

typedef struct Scena08Spark {
    u8  active;      /* 0x00 - 0 marks a free slot */
    u8  kind;        /* 0x01 - selects the per-frame handler */
    u8  life;        /* 0x02 - frames left */
    u8  fade;        /* 0x03 - shade added per frame */
    u8  life_reload; /* 0x04 - frames loaded into life when it runs out */
    u8  pad_05[3];
    s32 speed;  /* 0x08 - vertical speed */
    s32 x;      /* 0x0C */
    s32 y;      /* 0x10 */
    s32 z;      /* 0x14 */
    s32 unk_18; /* 0x18 */
} Scena08Spark;

ASSERT_SIZE(Scena08Spark, 0x1C);
ASSERT_OFFSET(Scena08Spark, active, 0x00);
ASSERT_OFFSET(Scena08Spark, kind, 0x01);
ASSERT_OFFSET(Scena08Spark, life, 0x02);
ASSERT_OFFSET(Scena08Spark, fade, 0x03);
ASSERT_OFFSET(Scena08Spark, life_reload, 0x04);
ASSERT_OFFSET(Scena08Spark, speed, 0x08);
ASSERT_OFFSET(Scena08Spark, x, 0x0C);
ASSERT_OFFSET(Scena08Spark, y, 0x10);
ASSERT_OFFSET(Scena08Spark, z, 0x14);
ASSERT_OFFSET(Scena08Spark, unk_18, 0x18);

extern void (*D_801FE8FC[])(Scena08Spark* spark);

void          func_801F7DE8(void);
s32           func_801F7E14(void);
void          func_801F8AE8(void);
u8            func_801F8BF8(void);
Scena08Spark* func_801F8B14(void);
void          func_801F8B50(Scena08Spark* spark);
void          func_801F81F4(u16 value);

void func_801F9688(void);

extern Callback D_801FE908[];
extern Callback D_801FE910[];
extern Callback D_801FE938[];
extern Callback D_801FE964[];

extern Callback  D_801FE970[];
/* D_801FE9C0 */
extern SceneFunc g_SceneActorDispatch[];
extern u16       D_801FE9EC[];

void func_801FE800(void);

void func_801F8964(Scena08Spark* spark);
void func_801F8D98(void* table);
void func_801F90C8(void* table);
void func_801FA32C(void);
void func_801FE12C(void);

void func_801FA19C(WorldPos* pos, s32* vx);

void func_801F9F8C(WorldPos* pos, s32 arg1, s32 arg2, s32 arg3);

void func_801F85F0(s32 x, s32 y, s32 angle);
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
    SND_PlayCue(cue);                                \
    g_Task->header.mode += 1;

#endif
