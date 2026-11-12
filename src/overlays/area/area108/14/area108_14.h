#ifndef OVERLAY_WORLD02_AREA108_14_H
#define OVERLAY_WORLD02_AREA108_14_H

/* The world02/area108/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "overlays/area/AreaSprite.h"
#include "overlays/area/world02.h"
#include "area/spad.h"
#include <rand.h>

extern u8* D_80147B40;
/* The cell the party leader's choice commits and the bit the event sets. */
extern s16 D_80147B26[];
extern u8  D_80147CC8;

/* One staged party cell: its x, y and facing. */
typedef struct AreaCellEntry {
    u8 x;
    u8 y;
    u8 facing;
} AreaCellEntry;

ASSERT_SIZE(AreaCellEntry, 0x03);

extern AreaCellEntry D_801F636C[];

void func_801F3588(u8* dst, u8* src, u16* state);

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0x04

typedef struct Area108Scratch {
    u8       unk_00[0x34];
    Point3DL pos;
} Area108Scratch;

ASSERT_SIZE(Area108Scratch, 0x40);
ASSERT_OFFSET(Area108Scratch, pos, 0x34);

/* One placement row: a whole coordinate per axis and whether it sits half a cell on. */
typedef struct AreaPosEntry {
    u8 x;
    u8 x_half;
    u8 y;
    u8 y_half;
} AreaPosEntry;

ASSERT_SIZE(AreaPosEntry, 0x04);

/* Place the actor on the row of `table` that the current stage number selects. */
#define AREA_PLACE_ACTOR(table)                                     \
    do {                                                            \
        u32 i = (u8)(D_80147B67 - 1);                               \
                                                                    \
        COORD_INT(g_Task->pos.x)  = (table)[i].x;                   \
        COORD_FRAC(g_Task->pos.x) = ((table)[i].x_half != 0) << 15; \
        COORD_INT(g_Task->pos.y)  = (table)[i].y;                   \
        COORD_FRAC(g_Task->pos.y) = ((table)[i].y_half != 0) << 15; \
    } while (0)

/* The game-overlay state bytes the cancel path resets. */
extern u8       D_80147AF0;
extern u8       D_80147B67;
extern u8       D_801F56E8[];
extern Callback D_801F56F4[];
extern u8       D_801F56FC[];
extern u8       D_801F5718[];
extern u8       D_801F63C4[];
extern u8*      D_801F63EC;

void func_801F2D40(const void* sprite);
void func_801F2F1C(void* sprite);
void func_801F2FC8(void);
u8   func_801F321C(void);
void func_801F3C84(void);

extern Point2D D_801F63DC[];

void func_801F55F0(u8 raise);

s32  func_801F3034(void);
void func_801F34B8(void);

void func_801F4160(s32 arg0, s32 arg1);

extern AreaPosEntry D_801F637C[];

extern AreaPosEntry D_801F63A0[];

#endif
