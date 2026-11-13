#ifndef OVERLAY_SCENARIO_SCENA09_00_H
#define OVERLAY_SCENARIO_SCENA09_00_H

/* The scenario/scena09/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

extern u8       D_80144908[];
extern u8       D_80145F09;
extern u8       D_80146865;
extern u8       D_80146866;
extern u8       D_80146867;
extern u8       D_8014623B;
extern u8       D_80146874;
extern u8       D_80146875;
extern u16      D_80146876;
extern u32      D_801F6C00;
/* D_801FE384 */
extern Callback g_SceneEntityDispatch[];

/* The triangle rows func_801F7424 offsets the projected point by: the second
 * and third vertex relative to the first, in screen space. */
typedef struct SceneTriangleOffset {
    u16 dx1;
    u16 dy1;
    u16 dx2;
    u16 dy2;
} SceneTriangleOffset;

ASSERT_SIZE(SceneTriangleOffset, 8);
ASSERT_OFFSET(SceneTriangleOffset, dy1, 0x02);
ASSERT_OFFSET(SceneTriangleOffset, dx2, 0x04);
ASSERT_OFFSET(SceneTriangleOffset, dy2, 0x06);

extern SceneTriangleOffset D_801FE38C[];
extern Callback            D_801FE3E0[];
extern Callback            D_801FE3EC[];
extern u8                  D_801FE430[4];

#define SCENE_SPARK_COUNT 32

/* One of the 32 sparks at AREA_WORK + 0x800: it falls by its velocity and is drawn
 * while its life runs. */
typedef struct SceneSpark {
    u8       active; /* 0x00 */
    u8       unk_01; /* 0x01 */
    u8       life;   /* 0x02 */
    u8       shade;  /* 0x03 */
    u8       frame;  /* 0x04 - indexes the 8-byte corner table */
    u8       pad_05[3];
    s32      vx; /* 0x08 */
    s32      vy; /* 0x0C */
    s32      vz; /* 0x10 */
    u8       pad_14[4];
    Point3DL pos;       /* 0x18 */
    u8       pad_24[4]; /* 0x24 */
} SceneSpark;

ASSERT_SIZE(SceneSpark, 0x28);
ASSERT_OFFSET(SceneSpark, vx, 0x08);
ASSERT_OFFSET(SceneSpark, vz, 0x10);
ASSERT_OFFSET(SceneSpark, pos, 0x18);

/* func_801F7574 */
void Scene_ClearWorkRows(void);
s32  func_801F75BC(void);
void func_801F76D0(void);

/* D_801FE434 */
extern SceneFunc g_SceneActorDispatch[];

extern u8 D_801FE474;
extern s8 (*D_801FE4BC[])(void);

#endif
