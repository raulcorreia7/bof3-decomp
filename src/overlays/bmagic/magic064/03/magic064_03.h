#ifndef OVERLAY_BMAGIC_MAGIC064_03_H
#define OVERLAY_BMAGIC_MAGIC064_03_H

/* The bmagic/magic064/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The twelve step callbacks at D_801EEC10, copied to the stack and indexed by the work state byte. */
#define BMAGIC064_STEP_COUNT 12

typedef struct BMagic064Steps {
    Callback handlers[BMAGIC064_STEP_COUNT];
} BMagic064Steps;

extern BMagic064Steps D_801EEC10;

#define MAGIC064_STEP_COUNT 4

typedef struct Magic064Steps {
    Callback steps[MAGIC064_STEP_COUNT];
} Magic064Steps;

#define MAGIC064_SECOND_STEP_COUNT 3

typedef struct Magic064SecondSteps {
    Callback steps[MAGIC064_SECOND_STEP_COUNT];
} Magic064SecondSteps;

extern Magic064Steps       D_801EEC40;
extern Magic064SecondSteps D_801EEC50;
extern Magic064SecondSteps D_801EEC70;

/* The record D_801F28B4 points at: a ring of line segments that spreads from its centre. */
typedef struct Magic064Ring {
    u8    unk_00;
    u8    mode;        /* +0x01 the handler func_801F0448 runs */
    s16   angle;       /* +0x02 the angle of the first segment */
    s32   x;           /* +0x04 the centre */
    s32   y;           /* +0x08 */
    Coord inner;       /* +0x0C the inner radius, 16.16 */
    Coord outer;       /* +0x10 the outer radius, 16.16 */
    s32   inner_speed; /* +0x14 added to the inner radius each frame */
    s32   outer_speed; /* +0x18 added to the outer radius each frame */
} Magic064Ring;

extern Magic064Ring* D_801F28B4;

/* The 0xC0 rings; func_801F009C runs each live one through D_801F28B4. */
#define MAGIC064_RING_COUNT 0xC0

extern Magic064Ring D_801F13B4[MAGIC064_RING_COUNT];

/* The five step handlers of func_801F009C, copied to the stack and run by header.step. */
#define MAGIC064_RING_STEP_COUNT 5

typedef struct Magic064RingSteps {
    Callback steps[MAGIC064_RING_STEP_COUNT];
} Magic064RingSteps;

extern Magic064RingSteps D_801EEC5C;

/* The screen offset of the ring centre from a battler, by facing. */
extern s8 D_801F138C[][2];

/* One sprite cell's texture coordinates: u and v of the cell in the effect's texture page. */
typedef UPoint2D Magic064SpriteUv;

extern Magic064SpriteUv D_801F13A4[];

void func_801EF8F4(void);
void func_801F001C(void);
void func_801F04A0(void);

void func_801F03D8(void);
void func_801F0448(void);
void func_801F0B8C(s16 x0, s16 y0, s16 x1, s16 y1);
void func_801F0EEC(u32 sprite, s32 blend, s32 color);
void func_801F103C(void);

/* The field map renderer state this image rebuilds, declared as the engine declares it in
 * src/engine/slus/slus.h. */
typedef struct AreaCell {
    u8  tile_x;
    u8  tile_y;
    u16 prim_id; /* low 12 bits: the g_AreaCellPrims row; upper bits are flags */
} AreaCell;

extern AreaCell g_AreaCells[56][28];
extern POLY_FT4 g_AreaCellPrims[][2];
extern u16      g_AreaCellPrimFreeIds[0x400];
extern u16      g_AreaCellPrimFreeIndex;
extern s16      g_AreaGridColCursor;
extern s16      g_AreaGridRowCursor;
extern u16      D_80149336;
extern u8       D_8014933D;

void Area_LoadCellRowsNext(void);
void Area_LoadCellRowsPrev(void);
void func_80154438(void);
void BMagic_ProjectCell(s32 px, s32 py, AreaCell* out);

#endif
