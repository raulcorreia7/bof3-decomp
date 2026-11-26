#ifndef OVERLAY_SCENARIO_SCENA00_00_H
#define OVERLAY_SCENARIO_SCENA00_00_H

#define FAKE_DECL_GAME_SCRATCH_BASE_SCALAR
#include "common/vector.h"
#include "overlays/scenario/scenario.h"
#include "common/util.h"

/* Scene_DrawTriangle: the third vertex is `size` rotated by this angle
 * (4096 per turn); the vertices are grey (r = g = b) at these levels. */
#define SCN_TRI_APEX_ANGLE 0x4F
#define SCN_TRI_SHADE_V0   0x28
#define SCN_TRI_SHADE_V1   0x6E
#define SCN_TRI_SHADE_V2   0x64

/* g_ScriptVars[2] in func_801FA7D8: retail loads every access through its own `lui $r, %hi(D_80146866)`; the array
 * member shares one %hi across the accesses and the function grows by 12 bytes (an absolute address and a local
 * pointer also move bytes). */
extern u8 D_80146866;

#define g_AreaLoads               ((void**)g_AreaLoads)

#define SCENE_EFFECT_SLOT_COUNT   30
#define SCENE_EFFECT_CELL_COUNT   12
#define SCENE_EFFECT_WEIGHT_COUNT 3

/* One row of the sample table at g_PartyActors[2].script: twelve sample offsets and three
 * weights per 0x28-byte record. */

/* The stride is a retail read: func_801FC01C walks the table as `(SceneSample *)(i * 0x28 + base)`. Twelve s16 samples sit at +0x02..+0x18 and the shifted weight halfwords at +0x1A..+0x1E; only the halfwords read here are named, the rest stays unresolved padding. */
typedef struct SceneSample {
    u8  unk_00[2];
    s16 sample[SCENE_EFFECT_CELL_COUNT];
    s16 weight[SCENE_EFFECT_WEIGHT_COUNT];
    u8  unk_20[8];
} SceneSample;

ASSERT_SIZE(SceneSample, 0x28); /* the same 0x28 row as area108's SceneSampleTrack, whose weights are u16 */

/* Field-space endpoints passed by value to func_801F78EC. */
typedef struct SceneLinePoint {
    s32   x;
    s32   y;
    Coord z;
} SceneLinePoint;

ASSERT_OFFSET(SceneLinePoint, x, 0x00);
ASSERT_OFFSET(SceneLinePoint, y, 0x04);
ASSERT_OFFSET(SceneLinePoint, z, 0x08);
ASSERT_SIZE(SceneLinePoint, 0x0C);

/* Scene effects: func_801F7134 draws the actor-relative sprite;
 * func_801F78EC draws its field-space lines and Scene_DrawTriangle its rotated triangles. */
typedef struct SceneEffect {
    u8             pad_00[0x1];
    /* 0x01 */ u8  step; /* the scenario step byte */
    u8             pad_02[0x4];
    u8             channel_06; /* the 0x238 animation channel */
    u8             channel_07; /* the 0x71C animation channel */
    u8             channel_08; /* the 0xE3 animation channel */
    u8             counter_09; /* the step counter */
    u8             channel_0A; /* the 0x31C animation channel */
    u8             channel_0B; /* the third animation channel */
    s32            counter_0C; /* a counter bounded by 0x80 */
    s32            counter_10; /* a counter bounded by 0xB6 */
    u8             pad_14[0x4];
    s32            channel_18; /* the first animation channel */
    s32            channel_1C; /* the second animation channel */
    s32            channel_20; /* the 0xC00 animation channel */
    u8             pad_24[0x5];
    s8             ot_index;
    u8             pad_2A[0x4];
    Pos2u          origin;
    u8             pad_32[0x2];
    SceneLinePoint pos; /* 0x34 */
    u8             pad_40[0x14];
    u32            unk_54;
    u8             pad_58[0x5];
    ColorRGB8      color;     /* +0x5D..0x5F: setRGB0 source, func_801F7134 and func_801F8BCC */
    /* 0x60 */ s32 projected; /* RotTransPers depth result */
    Angle3         angle;
} SceneEffect;

ASSERT_OFFSET(SceneEffect, step, 0x01);
ASSERT_OFFSET(SceneEffect, channel_18, 0x18);
ASSERT_OFFSET(SceneEffect, pos, 0x34);
ASSERT_SIZE(SceneEffect, 0x70);
STATIC_ASSERT(SceneEffect_pos_z, DECOMP_OFFSETOF(SceneEffect, pos.z) == 0x3C);
ASSERT_OFFSET(SceneEffect, unk_54, 0x54);
ASSERT_OFFSET(SceneEffect, color, 0x5D);
ASSERT_OFFSET(SceneEffect, projected, 0x60);
ASSERT_OFFSET(SceneEffect, angle, 0x64);

/* The payload prologue at 0x801F6C00: the type-0 EMI loader compares the
 * first word with the archive TOC's cached first word
 * (@source: wiki:formats/emi); the second word holds the line colour:
 * func_801F7670 reads its first three bytes (D_801F6C04..D_801F6C06). */
typedef struct Scene00OverlayHeader {
    OverlayHeader overlay;
    u32           unk_04; /* 0x04; the first three bytes are the line colour (D_801F6C04) */
} Scene00OverlayHeader;

ASSERT_OFFSET(Scene00OverlayHeader, overlay, 0x00);
ASSERT_OFFSET(Scene00OverlayHeader, unk_04, 0x04);
ASSERT_SIZE(Scene00OverlayHeader, 8);

/* The scenario line colour, copied from D_801F6C04 and passed to func_801F78EC by value. */
typedef ColorRGB8 SceneLineColor;

/* The shared table block at 0x801FC980..0x801FCA84, read through several
 * overlapping views: D_801FC980 and its sub-tables at +0x08, +0x1C, +0x2C
 * and +0x54 are state-handler pointer arrays; D_801FC9E8/D_801FC9E9 are s8
 * deltas; D_801FC9EC is an s8 array indexed by (work->counter_09 >> 2);
 * D_801FCA10 and D_801FCA1C are handler arrays; D_801FCA4C is a byte table
 * indexed by a value & 0xF; D_801FCA5C is a byte table indexed by a state;
 * and D_801FCA64/D_801FCA65 are byte pairs indexed by entry * 2. */
typedef struct Scene00Tables {
    Callback       handlers_00[26]; /* 0x000; D_801FC980, sub-views at +0x08/+0x1C/+0x2C/+0x54 */
    s8             unk_68;          /* 0x068 D_801FC9E8 */
    s8             unk_69;          /* 0x069 D_801FC9E9 */
    u8             pad_6A[2];
    s8             unk_6C[4];       /* 0x06C D_801FC9EC */
    u8             speed[12];       /* 0x070; no static reader */
    Callback       unk_7C[4];       /* 0x07C func_801F913C, Scene_DispatchActor, Scene_TestStepTrigger, func_801FC8F4 */
    /* 0x8C */ u32 zero;            /* 0x08C; null terminator */
    Callback       handlers_90[15]; /* 0x090 D_801FCA10; D_801FCA1C at +0x0C */
    u8             table_CC[16];    /* 0x0CC D_801FCA4C */
    u8             table_DC[8];     /* 0x0DC D_801FCA5C */
    u8             pairs[16][2];    /* 0x0E4 D_801FCA64/D_801FCA65 */
} Scene00Tables;

ASSERT_SIZE(Scene00Tables, 0x104);

/* The twelve s32 cells of one effect slot. */
typedef struct SceneEffectSlot {
    s32 cell[SCENE_EFFECT_CELL_COUNT];
} SceneEffectSlot;

ASSERT_SIZE(SceneEffectSlot, 0x30);

/* Cell `k` of the slot at byte offset `slot` in a SceneSampleEffect table. Retail addresses each
 * cell from the slot offset; indexing the table by slot number reorders the frame setup. */
#define SCENE_EFFECT_CELL(table, slot, k) (((SceneEffectSlot*)((u8*)(table) + (slot)))->cell[k])

/* The per-slot sample effect: func_801FC01C seeds it from the sample table at
 * g_PartyActors[2].script and func_801FC3A0 steps it every frame. `accum` is the 16.16 sample,
 * `delta` its per-frame step and `life_delta` the amount taken off the cell's
 * lifetime. */
typedef struct SceneSampleEffect {
    SceneEffectSlot delta[SCENE_EFFECT_SLOT_COUNT];
    SceneEffectSlot accum[SCENE_EFFECT_SLOT_COUNT];
    SceneEffectSlot life_delta[SCENE_EFFECT_SLOT_COUNT];
} SceneSampleEffect;

ASSERT_SIZE(SceneSampleEffect, 0x10E0);

/* One row of the per-slot effect arrays. */

extern s16* volatile D_1F800010;
/* D_801448FC */
/* D_801448FF */
/* D_80144900 */
/* D_80144904 */
extern u8                D_80145518[][4];
extern s32               D_801468A0;
extern s32               D_801468A4;
extern s32               D_801469EC;
extern s32               D_801469F0;
extern u32               D_80147B28;
extern SceneLineColor    D_801F6C04;
extern Callback          D_801FC980[];
extern Callback          D_801FC988[];
extern Callback          D_801FC99C[];
extern Callback          D_801FC9AC[];
extern Callback          D_801FC9D4[];
extern s8                D_801FC9E8;
extern s8                D_801FC9E9;
extern s8                D_801FC9EC[];
extern Callback          D_801FCA10[];
extern Callback          D_801FCA1C[];
extern u8                D_801FCA4C[];
extern u8                D_801FCA5C[];
extern u8                D_801FCA64[];
extern u8                D_801FCA65[];
/* D_801FCA90 */
extern SceneSampleEffect g_SceneEffect;

void func_80164020();
void func_801F6E04(void);
void func_801F6E48(void);
void func_801F7134(s32 chapter_id);
void func_801F7264(void);
void func_801F72A0(void);
void func_801F7350(void);
void func_801F73A8(void);
void func_801F7440(void);
void func_801F7670(void);
void func_801F78EC(volatile SceneLinePoint to, volatile SceneLinePoint from, SceneLineColor color);
void func_801F7A5C(void);
void func_801F7B0C(void);
void func_801F7B80(void);
void func_801F7C34(void);
void func_801F7CF0(void);
void func_801F7DC8(void);
void func_801F7EE0(void);
void func_801F8014(void);
void func_801F8140(void);
void func_801F82B4(void);
void func_801F8360(void);
/* func_801F85A8 */
void Scene_DrawTriangle(s32 size, s32 angle_x, s32 angle_y, s32 angle_z);
void func_801F8748(void);
void func_801F878C(void);
void func_801F882C(void);
void func_801F8930(void);
void func_801F89F0(void);
void func_801F8AB8(void);
void func_801F8BCC(void);
void func_801F8D70(void);
void func_801F8D90(void);
void func_801F913C(void);
void func_801F9178(void);
void func_801F92DC(void);
void func_801F9644(void);
void func_801F9868(void);
void func_801F9B98(void);
void func_801F9BE4(void);
void func_801F9FB8(void);
void func_801FA27C(void);
void func_801FA7D8(void);
void func_801FAF6C(void);
void func_801FB204(void);
void func_801FB620(void);
void func_801FB67C(void);
void func_801FB744(void);
void func_801FB924(void);
void func_801FBE88(void);
void Scene_DispatchActor(void* entity);
s32  Scene_TestStepTrigger(s32 x);

#endif
