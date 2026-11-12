#ifndef OVERLAY_SCENARIO_SCENA07_00_H
#define OVERLAY_SCENARIO_SCENA07_00_H

/* The scenario/scena07/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"
#define SCRATCH_ROW_STRIDE 0x1C
#define SCRATCH_ROW_OFFSET 0x00

void            func_801F3C3C(s32 value);
void            func_801F8358(void);
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
extern void (*D_801FDDF0[])(u8* row);

/* The spawn rows func_801FC094 reads: the cell position and the scene timer value that spawn an
 * actor there. Twelve rows fill the span up to D_801FDE88. */
typedef struct SceneTimerSpawn {
    u16 x;     /* +0x0 */
    u16 y;     /* +0x2 */
    s16 timer; /* +0x4 */
} SceneTimerSpawn;

ASSERT_SIZE(SceneTimerSpawn, 6);
ASSERT_OFFSET(SceneTimerSpawn, y, 0x02);
ASSERT_OFFSET(SceneTimerSpawn, timer, 0x04);
extern Callback        D_801FDE10[];
extern Callback        D_801FDE1C[];
extern SceneTimerSpawn D_801FDE40[12];
extern u8              D_801FDE88[4];
/* D_801FDF8C */
extern SceneFunc       g_SceneActorDispatch[];
extern u8              D_801FDFC4;

/* The record D_801FDFBC points at: a world position the burst draws around and its size. */
typedef struct Scena07Burst {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
    u16 unk_10;
} Scena07Burst;

/* The burst position record the start step fills. */
#define SCENA07_BURST_RECORD MEM_PTR(Scena07Burst, AREA_WORK + 0x948)

extern Scena07Burst* D_801FDFBC;
void                 func_801F97E0(Scena07Burst* burst);

/* The burst buffer D_801FDFC0 points at, at D_800E4C24: the burst position,
 * its rotation angle and the scale triple its draw function reads. The span
 * between the position and the angle is not modelled. */
typedef struct Scena07BurstBuffer {
    s32 x; /* 0x000 */
    s32 y; /* 0x004 */
    s32 z; /* 0x008 */
    u8  pad_00C[0x504];
    u16 angle; /* 0x510 */
    u8  pad_512[2];
    s32 unk_514; /* 0x514 */
    s32 unk_518; /* 0x518 */
    s32 unk_51C; /* 0x51C */
} Scena07BurstBuffer;

ASSERT_SIZE(Scena07BurstBuffer, 0x520);
ASSERT_OFFSET(Scena07BurstBuffer, angle, 0x510);
ASSERT_OFFSET(Scena07BurstBuffer, unk_514, 0x514);

extern Scena07BurstBuffer* D_801FDFC0;
void                       func_801F9330(Scena07BurstBuffer* buffer);

/* The burst rotation step func_801F7960 and func_801F7C9C share: draw the burst buffer, turn it by
 * the step while the countdown is high, and clear the actor when it ends. Every change must keep
 * both members matching. */
static inline void Scene_TurnBurst(s32 step) {
    func_801F9330(D_801FDFC0);
    if (g_Task->vx >= 9) {
        D_801FDFC0->angle += step;
    }
    if (--g_Task->vx == 0) {
        func_80196070();
    }
}

void func_801F81D4(u8* row);

/* The position setup func_801F7A30 and func_801F7D6C share: place the actor at the lead member's position and
 * sample the ground there. Every change must keep both members matching. */
static inline void Scene_PlaceAtLead(void) {
    g_Task->pos.x.fixed = g_Game.members[0].pos.x.fixed;
    g_Task->pos.y.fixed = g_Game.members[0].pos.y.fixed;
    g_Task->pos.z.fixed = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
}

u8*       func_801F8394(void);
void      func_801F83D0(u8* row);
void      func_801F88B8(void* table);
void      func_801F8BE8(void* table);
void      func_801FA38C(void);
extern u8 D_801FDFC8;

/* The panel's trail in the work memory, 32 rows of 0x18 bytes: the panel steps shift them down and
 * draw the first 31. kept: a folded constant, so a symbol cannot replace it without growing every
 * panel step. */
#define SCENA07_PANEL_ROWS MEM_PTR(void, AREA_WORK + 0xE0)

/* The panel fade step func_801F72E0 and func_801F80F0 share: draw the panel table, dim it by 12 and
 * advance the actor when its countdown ends. Every change must keep both members matching. */
#define SCENA07_PANEL_FADE_STEP()      \
    func_801F88B8(SCENA07_PANEL_ROWS); \
    func_801F8BE8(SCENA07_PANEL_ROWS); \
    D_800E4C1E -= 0xC;                 \
    if (--g_Task->timer == 0) {        \
        g_Task->header.step++;         \
    }

/* The panel brighten step func_801F724C and func_801F805C share: draw the panel table, brighten it by 6
 * and re-arm the countdown to 0x20 when it ends. Every change must keep both members matching. */
#define SCENA07_PANEL_BRIGHTEN_STEP()  \
    func_801F88B8(SCENA07_PANEL_ROWS); \
    func_801F8BE8(SCENA07_PANEL_ROWS); \
    D_800E4C1E += 6;                   \
    if (--g_Task->timer == 0) {        \
        g_Task->timer = 32;            \
        g_Task->header.step++;         \
    }
u8   func_801F85D8(void);
void func_801F9DA8(void);
u8   func_801F9EFC(void);

/* D_801FDD14 */
extern Callback g_SceneEntityDispatch[];

extern u8       D_80144EB8[];
extern u8       D_80146865;
extern u8       D_80146866;
extern u8       D_80146867;
extern u8       D_80146874;
extern u8       D_80146875;
/* D_801FDFA0 */
extern u8       g_ScenePositionTable;
/* D_801FDFA8 */
extern Callback g_ScenePositionDispatch[];
extern void (*D_801FDDF0[])(u8* row);
void func_801F81D4(u8* row);

s8 func_801A7AD8(u8* entry, u8 count, u16 x, u16 y);

#endif
