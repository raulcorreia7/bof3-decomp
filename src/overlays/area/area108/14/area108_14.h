#ifndef OVERLAY_WORLD02_AREA108_14_H
#define OVERLAY_WORLD02_AREA108_14_H

/* The world02/area108/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "overlays/area/shared/AreaSprite.h"
#include "overlays/area/worlds/world02.h"
#include <rand.h>

/* The vertex rows and the per-row transform state the stage animates. */
#define AREA108_VERTEX_DST   MEM_PTR(u8, AREA_WORK + 0x7A8)
#define AREA108_STATE_BASE   MEM_PTR(AreaTransform, AREA_WORK + 0x280)
#define AREA108_STATE_OFFSET MEM_PTR(u16, AREA_WORK + 0x284)

/* The cell the party leader's choice commits and the bit the event sets. */
extern s16 D_80147B26[];

/* A map cell and a facing: the spots the leader stands on to pick a branch (func_801F4414). */
typedef struct AreaFacingCell {
    u8 x;
    u8 y;
    u8 facing;
} AreaFacingCell;

ASSERT_SIZE(AreaFacingCell, 0x03);

extern AreaFacingCell D_801F636C[];

void func_801F3588(u8* dst, u8* src, AreaTransform* state);

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0x04

/* One placement row: a whole coordinate per axis and whether it sits half a cell on. */
typedef struct AreaPosEntry {
    u8 x;
    u8 x_half;
    u8 y;
    u8 y_half;
} AreaPosEntry;

ASSERT_SIZE(AreaPosEntry, 0x04);

/* Place the actor on the row of `table` that the current stage number selects. */
#define AREA_PLACE_ACTOR(table)                                          \
    do {                                                                 \
        u32 i = (u8)(g_PartyActors[1].unk_77 - 1);                       \
                                                                         \
        COORD_INT(TASK(Actor)->pos.x)  = (table)[i].x;                   \
        COORD_FRAC(TASK(Actor)->pos.x) = ((table)[i].x_half != 0) << 15; \
        COORD_INT(TASK(Actor)->pos.y)  = (table)[i].y;                   \
        COORD_FRAC(TASK(Actor)->pos.y) = ((table)[i].y_half != 0) << 15; \
    } while (0)

/* The game-overlay state bytes the cancel path resets. */
extern u8       D_801F56E8[];
extern Callback D_801F56F4[];
extern u8       D_801F56FC[];
extern u8       D_801F5718[];
extern u8       D_801F63C4[];
extern u8*      D_801F63EC;

void func_801F2D40(const void* sprite);
void func_801F2F1C(void* sprite);
void func_801F2FC8(void);
void func_801F321C(void);
void func_801F3C84(void);

extern Pos2 D_801F63DC[];

/* The stage quad's tile, palette and luminance word: the timer's top bits raise its luminance. */
#define AREA108_QUAD_WORD ((0x2510u << 16) | 0x0100u)

s32 func_801F3034(void);

void func_801F34B8(void);
void func_801F4160(s32 step, s32 shade);

u8   func_801F4F60(s32 x, s32 y);
void func_801F55F0(u8 raise);

extern AreaPosEntry D_801F637C[];

extern AreaPosEntry D_801F63A0[];

/* One row of the sample track the stage event steps: the twelve samples and the three weights
 * that add to them. */
typedef struct SceneSampleTrack {
    u8  unk_00[2];
    u16 sample[12];
    s16 weight[3];
    u8  unk_20[8];
} SceneSampleTrack;

ASSERT_OFFSET(SceneSampleTrack, sample, 0x02);
ASSERT_OFFSET(SceneSampleTrack, weight, 0x1A);
ASSERT_SIZE(SceneSampleTrack, 0x28); /* the same 0x28 row as scena00's SceneSample */

/* The staged actor rows: the event scrolls to row 1 and tints row 0. */

/* The sample rows the event fades: the row count, the event flag byte and the rows. */
typedef struct SceneSampleSet {
    s8                count;
    u8                unk_01[2];
    u8                flags;
    SceneSampleTrack* tracks;
} SceneSampleSet;

ASSERT_OFFSET(SceneSampleSet, flags, 0x03);
ASSERT_OFFSET(SceneSampleSet, tracks, 0x04);

extern SceneSampleSet D_801F6298;

/* The four trigger cells the stage event matches: the cell, the facing and the scene flag to toggle. */
typedef struct Area108Trigger {
    u8 x;
    u8 y;
    u8 facing;
    u8 flag;
} Area108Trigger;

ASSERT_SIZE(Area108Trigger, 0x04);

/* The trigger cell count the stage event walks. */
#define AREA108_TRIGGER_COUNT 4

extern Area108Trigger D_801F63CC[];

#endif
