#ifndef OVERLAY_SCENARIO_SCE15EF3_00_H
#define OVERLAY_SCENARIO_SCE15EF3_00_H

/* The scenario/sce15ef3/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

/* One 0x14-byte emitter of the table at AREA_WORK + 0x1800: it spawns two sparks each time its timer runs out. */
typedef struct SceneSparkEmitter {
    u8  active; /* +0x00 */
    u8  unk_1;  /* +0x01 */
    u8  unk_2;  /* +0x02 */
    u8  timer;  /* +0x03 */
    s32 x;      /* +0x04 */
    s32 y;      /* +0x08 */
    s32 z;      /* +0x0C */
    s32 unk_10; /* +0x10 */
} SceneSparkEmitter;

/* One 0x18-byte row of the sprite work table at AREA_WORK. */
typedef struct SceneSpark {
    u8  active; /* +0x00 */
    u8  unk_1;  /* +0x01 */
    u8  life;   /* +0x02 */
    u8  unk_3;  /* +0x03 */
    s32 x;      /* +0x04 */
    s32 y;      /* +0x08 */
    s32 z;      /* +0x0C */
    s32 unk_10; /* +0x10 */
    s32 unk_14; /* +0x14 */
} SceneSpark;

ASSERT_SIZE(SceneSparkEmitter, 0x14);
ASSERT_SIZE(SceneSpark, 0x18);
ASSERT_OFFSET(SceneSparkEmitter, timer, 0x03);
ASSERT_OFFSET(SceneSpark, unk_14, 0x14);

#define g_SparkEmitters     ((SceneSparkEmitter*)(AREA_WORK + 0x1800))
#define SPARK_EMITTER_COUNT 8

#define g_ScanBars          ((ScanBar*)(AREA_WORK + 0x18A0))

extern u32      D_801D0C00;
/* D_801D27C0 */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801D27CC[];
extern Callback D_801D27D8[];
extern Callback D_801D27EC[];
extern Callback D_801D2800[];

extern Callback D_801D280C[];

void func_801D16DC(void);
/* func_801D25EC */
void Scene_ClaimScanBar(void);
s32  func_801D18CC(void);
s32  func_801D1A60(void);
void func_801D1FF8(Point3l* pos, s16 x, s16 y, u16 angle, u8 colour, u8 shade);
/* func_801D230C */
void Scene_SetXFixed(void);
/* func_801D23AC */
void Scene_DrawRedFade(u8 red);

void func_801D19A0(void);

void func_801D1D20(WorldPos* pos, s32* step, u8 arg2, u8 arg3);

#endif
