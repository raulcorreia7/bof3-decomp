#ifndef OVERLAY_WORLD01_AREA067_14_H
#define OVERLAY_WORLD01_AREA067_14_H

/* The world01/area067/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"
#include "area/spad.h"

extern void* D_80146954;
extern u8    D_801F4644[];
extern u8    D_801F464C[];
extern u8    D_801F4654[];
extern u16   D_801F5384[];
extern u16   D_801F5390[];
extern u16   D_801F539C[];
extern s32   D_801F53A0;
extern s32   D_801F53A4;

/* The ring a mode draws: the screen origin, the radius and vertical span of its
 * quads, and the angle its points step by. It overlays the task's velocity
 * words. */
typedef struct AreaRippleQuad {
    u16 x;      /* 0x00 */
    u16 y;      /* 0x02 */
    s16 radius; /* 0x04 */
    u16 height; /* 0x06 */
    u16 angle;  /* 0x08 */
} AreaRippleQuad;

ASSERT_OFFSET(AreaRippleQuad, x, 0x00);
ASSERT_OFFSET(AreaRippleQuad, y, 0x02);
ASSERT_OFFSET(AreaRippleQuad, radius, 0x04);
ASSERT_OFFSET(AreaRippleQuad, height, 0x06);
ASSERT_OFFSET(AreaRippleQuad, angle, 0x08);
ASSERT_SIZE(AreaRippleQuad, 0x0A);

void func_801F31C8(AreaRippleQuad* quad);
void func_801F3394(AreaRippleQuad* quad);
void func_801F358C(AreaRippleQuad* quad);
void func_801F3AD8(AreaRippleQuad* quad);
void func_801F38A0(s16* row);
s16* func_801F3A9C(void);
void func_801F3D54(s16* row);

#endif
