#ifndef OVERLAY_WORLD04_AREA174_13_H
#define OVERLAY_WORLD04_AREA174_13_H

/* The world04/area174/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The scratchpad cell holding this mode's work pointer. */

/* The current map row in the field-loader table. */
/* The party position in 16.16 fixed point. */
/* The payload's first words: the per-state handler pointers. */
extern u8       D_801F4FAC[];
/* The palette callbacks this overlay animates. */
extern Callback D_801F66D4[17];
/* The row table the step lookup reads through the load entry. */
extern u8*      D_801F6748[];
/* The signed per-step offsets the scripted move adds to x and subtracts from y, indexed by the 4-bit step. */
extern s8       D_801F6754[];

extern void Actor_BeginScript(u8 script_index, u16 position);
u8*         func_801F2E88(void);
extern u8   Area_UpdateShots(void);
extern void func_801F4A5C(u8* pairs, s32 facing);
extern void func_801F4B0C(void);

extern void func_801F4C68(void);

void func_801F2E5C(void);

typedef struct AreaShot {
    u8       pad_00[3];
    u8       active;
    u8       unk_04;
    u8       timer;
    u16      angle;
    s16      unk_08;
    s16      unk_0A;
    WorldPos pos;
    u8       pad_18[4];
    Point3DL velocity;
    u8       pad_28[4];
} AreaShot;

ASSERT_SIZE(AreaShot, 0x2C);
ASSERT_OFFSET(AreaShot, angle, 0x06);
ASSERT_OFFSET(AreaShot, pos, 0x0C);
ASSERT_OFFSET(AreaShot, velocity, 0x1C);

void func_801F2FEC(s32* pos, s16, s16, u16 angle, u8, u8);
void func_801F3378(AreaShot* shot);

#endif
