#ifndef OVERLAY_SCENARIO_SCENA00_00_H
#define OVERLAY_SCENARIO_SCENA00_00_H

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"
#include <abs.h>

/* func_801F85A8 triangle: the third vertex is `size` rotated by this angle
 * (4096 per turn); the vertices are grey (r = g = b) at these levels. */
#define SCN_TRI_APEX_ANGLE       0x4F
#define SCN_TRI_SHADE_V0         0x28
#define SCN_TRI_SHADE_V1         0x6E
#define SCN_TRI_SHADE_V2         0x64
#define SCN_EFFECT               ((SceneEffect*)g_SpadWork)
#define SPAD_ROW                 ((Actor*)g_SpadWork)

/* Cell `k` of the slot whose byte offset is `slot` (slot index * 0x30). */
#define SCENE_FX(table, slot, k) (((SceneFxCells*)((u8*)(table) + (slot)))->cell[k])
#define g_PartyX                 (*(u32*)&g_PartyX)
#define g_PartyY                 ((u32*)&g_PartyY)

/* g_ScriptVars[2] in func_801FA7D8: retail loads every access through its own `lui $r, %hi(D_80146866)`; the array
 * member shares one %hi across the accesses and the function grows by 12 bytes (an absolute address and a local
 * pointer also move bytes). */
extern u8 D_80146866;

#define g_AreaScrollTargetY ((u32*)&g_AreaScrollTargetY)
#define g_AreaLoads         ((void**)g_AreaLoads)

/* One row of the sample table at D_80147BD8: twelve sample offsets and three
 * weights per 0x28-byte record. */

/* One 0x28-byte entry of the source table at D_80147BD8, shared by
 * func_801FC01C and func_801FC3A0, which carried identical file-local copies.
 * The stride is a retail read: func_801FC01C walks the table as
 * `(SceneSampleRecord *)(i * 0x28 + base)`. Twelve s16 samples sit at
 * +0x02..+0x18 and the shifted weight halfwords at +0x1A..+0x1E; only the
 * halfwords read here are named, the rest stays unresolved padding. */
typedef struct SceneSampleRecord {
    u8  unk_00[2];
    s16 sample_02;
    s16 sample_04;
    s16 sample_06;
    s16 sample_08;
    s16 sample_0A;
    s16 sample_0C;
    s16 sample_0E;
    s16 sample_10;
    s16 sample_12;
    s16 sample_14;
    s16 sample_16;
    s16 sample_18;
    s16 weight_1A;
    s16 weight_1C;
    s16 weight_1E;
    u8  unk_20[8];
} SceneSampleRecord;

ASSERT_SIZE(SceneSampleRecord, 0x28);

/* Field elevation at +0x3C: func_801F74EC copies the actor's 16.16 height;
 * func_801F78EC projects its signed integer part. */
typedef union SceneElevation {
    s32 fixed_point; /* 0x00 */

    struct {
        u16 fraction; /* 0x00 */
        s16 height;   /* 0x02 */
    } parts;
} SceneElevation;

ASSERT_SIZE(SceneElevation, 4);
ASSERT_OFFSET(SceneElevation, fixed_point, 0x00);
ASSERT_OFFSET(SceneElevation, parts, 0x00);
STATIC_ASSERT(SceneElevation_parts_height, DECOMP_OFFSETOF(SceneElevation, parts.height) == 2);

/* Field-space endpoints passed by value to func_801F78EC. */
typedef struct SceneLinePoint {
    s32            x;
    s32            y;
    SceneElevation z;
} SceneLinePoint;

ASSERT_SIZE(SceneLinePoint, 0x0C);
ASSERT_OFFSET(SceneLinePoint, x, 0x00);
ASSERT_OFFSET(SceneLinePoint, y, 0x04);
ASSERT_OFFSET(SceneLinePoint, z, 0x08);

/* Scene effects: func_801F7134 draws the actor-relative sprite;
 * func_801F78EC draws its field-space lines and func_801F85A8 its rotated triangles. */
typedef struct SceneEffect {
    u8                        pad_00[0x1];
    /* 0x01 */ u8             step; /* the scenario step byte */
    u8                        pad_02[0x4];
    u8                        channel_06; /* the 0x238 animation channel */
    u8                        channel_07; /* the 0x71C animation channel */
    u8                        channel_08; /* the 0xE3 animation channel */
    u8                        counter_09; /* the step counter */
    u8                        channel_0A; /* the 0x31C animation channel */
    u8                        channel_0B; /* the third animation channel */
    s32                       counter_0C; /* a counter bounded by 0x80 */
    s32                       counter_10; /* a counter bounded by 0xB6 */
    u8                        pad_14[0x4];
    s32                       channel_18; /* the first animation channel */
    s32                       channel_1C; /* the second animation channel */
    s32                       channel_20; /* the 0xC00 animation channel */
    u8                        pad_24[0x5];
    s8                        ot_index;
    u8                        pad_2A[0x4];
    /* 0x2E */ u16            origin_x;
    /* 0x30 */ u16            origin_y;
    u8                        pad_32[0x2];
    /* 0x34 */ s32            pos_x;
    /* 0x38 */ s32            pos_y;
    /* 0x3C */ SceneElevation z;
    u8                        pad_40[0x14];
    u32                       unk_54;
    u8                        pad_58[0x5];
    u8                        color_r; /* +0x5D..0x5F: setRGB0 source, func_801F7134 and func_801F8BCC */
    u8                        color_g;
    u8                        color_b;
    /* 0x60 */ s32            projected; /* RotTransPers depth result */
    /* 0x64 */ s32            angle_x;   /* the X rotation angle */
    /* 0x68 */ s32            angle_y;   /* the Y rotation angle */
    /* 0x6C */ s32            angle_z;   /* the Z rotation angle */
} SceneEffect;

ASSERT_SIZE(SceneEffect, 0x70);
ASSERT_OFFSET(SceneEffect, step, 0x01);
ASSERT_OFFSET(SceneEffect, channel_18, 0x18);
ASSERT_OFFSET(SceneEffect, pos_x, 0x34);
ASSERT_OFFSET(SceneEffect, z, 0x3C);
ASSERT_OFFSET(SceneEffect, unk_54, 0x54);
ASSERT_OFFSET(SceneEffect, color_r, 0x5D);
ASSERT_OFFSET(SceneEffect, projected, 0x60);
ASSERT_OFFSET(SceneEffect, angle_x, 0x64);
ASSERT_OFFSET(SceneEffect, angle_z, 0x6C);

/* Camera scroll word at 0x80143F84; the halfword at +2 is read signed. */
typedef union AreaScroll {
    u32 raw;
    s16 half[2];
} AreaScroll;

ASSERT_SIZE(AreaScroll, 4);
ASSERT_OFFSET(AreaScroll, raw, 0x00);
ASSERT_OFFSET(AreaScroll, half, 0x00);

/* The payload prologue at 0x801F6C00: the type-0 EMI loader compares the
 * first word with the archive TOC's cached first word
 * (@source: wiki:formats/emi); the second word holds the line colour:
 * func_801F7670 reads its first three bytes (D_801F6C04..D_801F6C06). */
typedef struct Scene00Head {
    SceneOverlayHeader overlay;
    u32                unk_04; /* 0x04; the first three bytes are the line colour (D_801F6C04) */
} Scene00Head;

ASSERT_SIZE(Scene00Head, 8);
ASSERT_OFFSET(Scene00Head, overlay, 0x00);
ASSERT_OFFSET(Scene00Head, unk_04, 0x04);

/* The three scenario line-color bytes copied from D_801F6C04 and passed to
 * func_801F78EC as one three-byte argument. */
typedef struct SceneLineColor {
    s8 r;
    s8 g;
    s8 b;
} SceneLineColor;

ASSERT_SIZE(SceneLineColor, 3);
ASSERT_OFFSET(SceneLineColor, r, 0);
ASSERT_OFFSET(SceneLineColor, g, 1);
ASSERT_OFFSET(SceneLineColor, b, 2);

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
    s8             unk_6C[4];  /* 0x06C D_801FC9EC */
    u8             unk_70[12]; /* 0x070; no static reader */
    Callback       unk_7C[4];  /* 0x07C func_801F913C, Scene_DispatchActor, Scene_CheckStepTrigger, func_801FC8F4 */
    /* 0x8C */ u32 zero;       /* 0x08C; null terminator */
    Callback       handlers_90[15]; /* 0x090 D_801FCA10; D_801FCA1C at +0x0C */
    u8             table_CC[16];    /* 0x0CC D_801FCA4C */
    u8             table_DC[8];     /* 0x0DC D_801FCA5C */
    u8             pairs_E4[16][2]; /* 0x0E4 D_801FCA64/D_801FCA65 */
} Scene00Tables;

ASSERT_SIZE(Scene00Tables, 0x104);

/* Per-slot effect work arrays: twelve s32 cells at a 0x30-byte stride. The
 * scratch source values at D_801FCA90, the accumulators at D_801FD030 and
 * the per-cell lifetimes at D_801FD5D0 share the same slot stride. */
typedef struct SceneFxCells {
    s32 cell[12];
} SceneFxCells;

ASSERT_SIZE(SceneFxCells, 0x30);

/* One row of the per-slot effect arrays. */

extern s16* volatile D_1F800010;
extern u16            g_GameAreaId;
extern u8             g_GameRequestKind;
extern AreaScroll     D_80143F84;
extern volatile u16   D_801448FC;
extern volatile u8    D_801448FF;
extern volatile u32   D_80144900;
extern volatile u32   D_80144904;
extern u8             D_80145518[][4];
extern u8             D_80145EB4;
extern u32            D_80145EC4;
extern u8             D_80146890;
extern s32            D_801468A0;
extern s32            D_801468A4;
extern s32            D_801469EC;
extern s32            D_801469F0;
extern u8             D_80147A58[];
/* One s32; the array form is kept because the scalar form changes the bytes of 8.c. */
extern s32            g_AreaFocusY[];
extern u16            D_80147A86;
extern u16            D_80147A88;
extern u16            D_80147A96;
extern s32            D_80147ABC;
extern s32            D_80147AC0;
extern u32            D_80147B28;
extern s32            D_80147BA0;
extern s32            D_80147BA4;
extern u8*            D_80147BD8;
extern s8*            D_80147BDC;
extern s32            D_80147BEC[];
extern s32            D_80147BF0[];
extern u8             D_80147C21;
extern s32            D_80147C38;
extern s32            D_80147C3C;
extern s32            D_80147C54;
extern s32            D_80147C58;
extern s16            g_AreaTileOriginY;
extern SceneLineColor D_801F6C04;
extern Callback       D_801FC980[];
extern Callback       D_801FC988[];
extern Callback       D_801FC99C[];
extern Callback       D_801FC9AC[];
extern Callback       D_801FC9D4[];
extern s8             D_801FC9E8;
extern s8             D_801FC9E9;
extern s8             D_801FC9EC[];
extern Callback       D_801FCA10[];
extern Callback       D_801FCA1C[];
extern u8             D_801FCA4C[];
extern u8             D_801FCA5C[];
extern u8             D_801FCA64[];
extern u8             D_801FCA65[];
extern SceneFxCells   D_801FCA90[];
extern u8             D_801FCA94;
extern u8             D_801FCA98;
extern u8             D_801FCA9C;
extern u8             D_801FCAA0;
extern u8             D_801FCAA4;
extern u8             D_801FCAA8;
extern u8             D_801FCAAC;
extern u8             D_801FCAB0;
extern u8             D_801FCAB4;
extern u8             D_801FCAB8;
extern u8             D_801FCABC;
extern SceneFxCells   D_801FD030[];
extern u8             D_801FD034;
extern u8             D_801FD038;
extern u8             D_801FD03C;
extern u8             D_801FD040;
extern u8             D_801FD044;
extern u8             D_801FD048;
extern u8             D_801FD04C;
extern u8             D_801FD050;
extern u8             D_801FD054;
extern u8             D_801FD058;
extern u8             D_801FD05C;
extern SceneFxCells   D_801FD5D0[];
extern u8             D_801FD5D4;
extern u8             D_801FD5D8;
extern u8             D_801FD5DC;
extern u8             D_801FD5E0;
extern u8             D_801FD5E4;
extern u8             D_801FD5E8;
extern u8             D_801FD5EC;
extern u8             D_801FD5F0;
extern u8             D_801FD5F4;
extern u8             D_801FD5F8;
extern u8             D_801FD5FC;

s32  Area_StepCameraAngle(s32 degrees, s8 duration);
void func_80164020(u32 arg0, u32 arg1);
void Scene_RequestChapterAdvance(void);
void Area_ProjectPoint(s32* pos, long* screen_xy);
void func_801BFE34(s32 work_kind, s32 work_index, s32 work_mode);
void Battle_StartScripted(u8 mode_byte);
void func_801F6E04(void);
void func_801F6E48(void);
void func_801F7134(s32 chapter_id);
void func_801F7264(void);
void func_801F72A0(void);
void func_801F7350(void);
void func_801F73A8(void);
void func_801F7440(void);
void func_801F7670(void);
void func_801F78CC(void);
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
void func_801F85A8(s32 size, s32 angle_x, s32 angle_y, s32 angle_z);
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
void func_801F9BD4(void);
void func_801F9BDC(void);
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
void func_801FC810(void);
s32  Scene_CheckStepTrigger(s32 x);
s32  func_801FC8F4(void);

#endif
