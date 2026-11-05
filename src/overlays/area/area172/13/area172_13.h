#ifndef OVERLAY_WORLD04_AREA172_13_H
#define OVERLAY_WORLD04_AREA172_13_H

/* The world04/area172/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"
#include "shared/WorldSpin.h"

/* The spin triangle record of src/overlays/area/area024/14/area024_14.h,
 * whose fields the shared spin passes read. */
typedef struct AreaSpin {
    s32     origin_x;
    s32     origin_y;
    s32     origin_z;
    u8      unk_0C[4];
    SVECTOR vertex_a;
    SVECTOR vertex_b;
    s16     angle_lo;
    s16     angle_hi;
    s16     spin_angle;
    s16     unk_26;
    s16     scale;
    s16     fade;
} AreaSpin;

#define AREA_SPIN_RADIUS     24
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x3
#define AREA_SPIN_SCALE_BASE 4
#define AREA_SPIN_FADE       0

/* The scratchpad cell holding this mode's work pointer. */

/* The payload's first words: the per-state handler pointers. */
extern u8 D_801F507C[];

/* The overlay's flag word. */

extern void Area_SetCellCode(s16 column, s16 row, u8 code);
extern void func_801F2DF4(s32 arg0);
void        func_801F4E8C(s32 x, s32 y);
void        func_801F47F0(void);

extern u8 D_80146874;

extern u8 D_80146875;

extern u8 D_80144EF8[];

/* func_801F38E8 */
void Area_ClaimSpawnSlot(void);
s32  Area_StepSpawnSlots(void);
/* func_801F3A38 */
void Area_DrawSpawnSlot(AreaSpawnSlot* slot);

#define AREA_SPAWN_SLOT_LIFE        0x20
#define AREA_SPAWN_SLOT_RADIUS      0x180
#define AREA_SPAWN_SLOT_CORE_SHADE  g_SpadWork->tint.bytes.unk_5D
#define AREA_SPAWN_SLOT_RADIUS_STEP 0xC

#endif
