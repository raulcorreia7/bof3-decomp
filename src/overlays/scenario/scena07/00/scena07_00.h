#ifndef OVERLAY_SCENARIO_SCENA07_00_H
#define OVERLAY_SCENARIO_SCENA07_00_H

/* The scenario/scena07/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/effects.h"

void            func_801F3C3C(s32 value);
void            func_801F8358(void);
bool            func_801FDA34(void);
extern u16      D_800E4C1E;
extern s8       D_80144EC0;
extern u32      D_801F6C00;
extern Callback D_801FDD3C[];
extern Callback D_801FDD48[];
extern Callback D_801FDD50[];
extern Callback D_801FDD70[];
extern Callback D_801FDD8C[];
extern Callback D_801FDDAC[];
extern Callback D_801FDDB4[];
extern Callback D_801FDDC0[];
extern Callback D_801FDDC8[];
extern Callback D_801FDDD0[];
extern void (*D_801FDDF0[])(FallingSpark* spark);

/* One 32-byte row of the effect table at AREA_WORK + 0x95C; a row is free while active is 0. */
typedef struct SceneEffectRow {
    u8  active; /* +0x00 */
    u8  unk_1;  /* +0x01 */
    u8  unk_2;  /* +0x02 */
    u8  unk_3;  /* +0x03 */
    s32 x;      /* +0x04 */
    s32 y;      /* +0x08 */
    s32 unk_C;  /* +0x0C */
    s32 unk_10; /* +0x10 */
    s32 unk_14; /* +0x14 */
    s32 unk_18; /* +0x18 */
    s32 unk_1C; /* +0x1C */
} SceneEffectRow;

ASSERT_OFFSET(SceneEffectRow, x, 0x04);
ASSERT_OFFSET(SceneEffectRow, unk_1C, 0x1C);
ASSERT_SIZE(SceneEffectRow, 0x20);

/* The spawn rows func_801FC094 reads: the cell position and the scene timer value that spawn an
 * actor there. Twelve rows fill the span up to D_801FDE88. */
typedef struct SceneTimerSpawn {
    u16 x;     /* +0x0 */
    u16 y;     /* +0x2 */
    s16 timer; /* +0x4 */
} SceneTimerSpawn;

ASSERT_OFFSET(SceneTimerSpawn, y, 0x02);
ASSERT_OFFSET(SceneTimerSpawn, timer, 0x04);
ASSERT_SIZE(SceneTimerSpawn, 6);
extern u8              D_801FDD7C[];
extern u8              D_801FDD84[];
extern u8              D_801FDD9C[];
extern u8              D_801FDDA4[];
extern Callback        D_801FDE10[];
extern Callback        D_801FDE1C[];
extern SceneTimerSpawn D_801FDE40[12];
extern u8              D_801FDE88[4];
extern u8              D_801FDE8C[];
extern u8              D_801FDF7C[];
/* D_801FDF8C */
extern u8              D_801FDFC4;

/* The record D_801FDFBC points at: a world position the burst draws around and its size. */
typedef struct Scena07Burst {
    VECTOR pos;
    u16    unk_10;
} Scena07Burst;

/* The burst position record the start step fills. */
#define SCENA07_BURST_RECORD MEM_PTR(Scena07Burst, AREA_WORK + 0x948)

extern Scena07Burst* D_801FDFBC;
void                 func_801F97E0(Scena07Burst* burst);

/* The burst buffer D_801FDFC0 points at, at D_800E4C24: the burst position,
 * the projected screen points of eight rows, their shades, its rotation angle and the scale triple its
 * draw function reads. */
typedef struct Scena07BurstBuffer {
    VECTOR  pos;           /* 0x000 */
    DVECTOR points[8][32]; /* 0x010 */
    u8      shade[8][32];  /* 0x410 */
    u16     angle;         /* 0x510 */
    u8      pad_512[2];
    s32     unk_514; /* 0x514 */
    s32     unk_518; /* 0x518 */
    s32     unk_51C; /* 0x51C */
} Scena07BurstBuffer;

ASSERT_OFFSET(Scena07BurstBuffer, points, 0x10);
ASSERT_OFFSET(Scena07BurstBuffer, shade, 0x410);
ASSERT_OFFSET(Scena07BurstBuffer, angle, 0x510);
ASSERT_OFFSET(Scena07BurstBuffer, unk_514, 0x514);
ASSERT_SIZE(Scena07BurstBuffer, 0x520);

extern Scena07BurstBuffer  D_800E4C24;
extern s16                 D_800E595C;
extern s16                 D_800E595E;
extern s16                 D_800E5960;
extern s32                 D_800E81D8;
extern s32                 D_800E81DC;
extern s32                 D_800E81E0;
extern Scena07BurstBuffer* D_801FDFC0;
void                       func_801F90F4(Scena07BurstBuffer* buffer);
void                       func_801F9330(Scena07BurstBuffer* buffer);

/* The burst rotation step func_801F7960 and func_801F7C9C share: draw the burst buffer, turn it by
 * the step while the countdown is high, and clear the actor when it ends. Every change must keep
 * both members matching. */
static inline void Scene_TurnBurst(s32 step) {
    func_801F9330(D_801FDFC0);
    if (SELF(Actor)->vx >= 9) {
        D_801FDFC0->angle += step;
    }
    if (--SELF(Actor)->vx == 0) {
        func_80196070();
    }
}

void func_801F81D4(FallingSpark* spark);

/* The position setup func_801F7A30 and func_801F7D6C share: place the actor at the lead member's position and
 * sample the ground there. Every change must keep both members matching. */
static inline void Scene_PlaceAtLead(void) {
    SELF(Actor)->pos.x.fixed = g_Game.members[0].pos.x.fixed;
    SELF(Actor)->pos.y.fixed = g_Game.members[0].pos.y.fixed;
    SELF(Actor)->pos.z.fixed = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) << 16;
}

void Scene_InitSpark(FallingSpark* spark);
void func_801F8478(FallingSpark* spark);
/* func_801F88B8 */
void Trail_Update(Trail* trail);

void      Trail_Draw(Trail* trail);
void      func_801FA38C(void);
extern u8 D_801FDFC8;

/* The panel's trail in the work memory: 32 points of 0x18 bytes. The panel steps shift them down
 * and draw the first 31. kept: a folded constant, so a symbol cannot replace it without growing
 * every panel step. */
#define SCENA07_TRAIL MEM_PTR(Trail, AREA_WORK + 0xE0)

/* The panel fade step func_801F72E0 and func_801F80F0 share: draw the panel table, dim it by 12 and
 * advance the actor when its countdown ends. Every change must keep both members matching. */
#define SCENA07_PANEL_FADE_STEP()    \
    Trail_Update(SCENA07_TRAIL);     \
    Trail_Draw(SCENA07_TRAIL);       \
    D_800E4C1E -= 0xC;               \
    if (--SELF(Actor)->timer == 0) { \
        SELF(Actor)->header.step++;  \
    }

/* The panel brighten step func_801F724C and func_801F805C share: draw the panel table, brighten it by 6
 * and re-arm the countdown to 0x20 when it ends. Every change must keep both members matching. */
#define SCENA07_PANEL_BRIGHTEN_STEP() \
    Trail_Update(SCENA07_TRAIL);      \
    Trail_Draw(SCENA07_TRAIL);        \
    D_800E4C1E += 6;                  \
    if (--SELF(Actor)->timer == 0) {  \
        SELF(Actor)->timer = 32;      \
        SELF(Actor)->header.step++;   \
    }
u8   func_801F85D8(void);
void func_801F9DA8(void);
u8*  func_801F9DD4(void);
u8   func_801F9EFC(void);

/* D_801FDD14 */

extern u8       D_80144DF5;
extern u8       D_80144EB8[];
/* D_801FDFA0 */
extern u8       g_ScenePositions;
/* D_801FDFA8 */
extern Callback g_ScenePositionDispatch[];
extern void (*D_801FDDF0[])(FallingSpark* spark);
extern u16 D_80146258;
void       func_801F81D4(FallingSpark* spark);

#endif
