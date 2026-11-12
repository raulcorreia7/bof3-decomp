#ifndef OVERLAY_WORLD01_AREA052_13_H
#define OVERLAY_WORLD01_AREA052_13_H

/* The world01/area052/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET 0x15
#define SCRATCH_ROW_STRIDE 0x18

extern u8 D_801F44B8[];
extern s8 D_801F5071;

/* One of the sixteen effect rows at the area work window: a rising, fading
 * textured quad. */
typedef struct AreaEffectRow {
    WorldPos pos;    /* 0x00 */
    s32      unk_0C; /* 0x0C */
    s32      unk_10; /* 0x10 */
    u8       unk_14; /* 0x14 */
    u8       active; /* 0x15 nonzero while the row is in use */
    u8       unk_16; /* 0x16 */
    u8       unk_17; /* 0x17 */
} AreaEffectRow;

ASSERT_OFFSET(AreaEffectRow, pos, 0x00);
ASSERT_OFFSET(AreaEffectRow, active, 0x15);
ASSERT_SIZE(AreaEffectRow, 0x18);

/* A rectangle of world cells that a scene event step tests the party against. */
typedef struct AreaTriggerRect {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
} AreaTriggerRect;

ASSERT_SIZE(AreaTriggerRect, 4);

extern AreaTriggerRect D_801F510C[2];
void                   func_801F2EC8(AreaEffectRow* row);
void                   func_801F3084(void);
void                   func_801F3194(void);
/* func_801F31C0 */
s32                    Area_UpdateEffectRows(void);
void                   func_801F3C4C(s32 x, s32 y);

void func_801F431C(void);

#endif
