#ifndef OVERLAY_BMAGIC_MAGIC109_03_H
#define OVERLAY_BMAGIC_MAGIC109_03_H

/* The bmagic/magic109/03 overlay: a swirl that twists the screen around the target. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The task record of this overlay. */
typedef struct Magic109Task {
    /* 0x00 */ TaskHeader  header;
    /* 0x03 */ u8          pad_03[6];
    /* 0x09 */ u8          radius;     /* half the side of the swirled square of the screen */
    /* 0x0A */ u8          timer;      /* frames the swirl holds its full size */
    /* 0x0B */ u8          twist_down; /* 1 while the twist falls, 0 while it rises */
    /* 0x0C */ u8          pad_0C[0x22];
    /* 0x2E */ ScreenCoord screen_x; /* the centre of the swirl */
    /* 0x30 */ ScreenCoord screen_y;
    /* 0x32 */ u8          pad_32[0x32];
    /* 0x64 */ s32         twist; /* the angle each ring turns by, per step of depth */
} Magic109Task;

ASSERT_OFFSET(Magic109Task, radius, 0x09);
ASSERT_OFFSET(Magic109Task, timer, 0x0A);
ASSERT_OFFSET(Magic109Task, twist_down, 0x0B);
ASSERT_OFFSET(Magic109Task, screen_x, 0x2E);
ASSERT_OFFSET(Magic109Task, screen_y, 0x30);
ASSERT_OFFSET(Magic109Task, twist, 0x64);

/* The swirl grows from its starting radius by BMAGIC_SWIRL_RADIUS_STEP per frame up to BMAGIC_SWIRL_RADIUS_MAX, holds
 * for BMAGIC_SWIRL_HOLD_FRAMES, then shrinks back to the starting radius. */
#define BMAGIC_SWIRL_RADIUS_START 2
#define BMAGIC_SWIRL_RADIUS_STEP  2
#define BMAGIC_SWIRL_RADIUS_MAX   0x54
#define BMAGIC_SWIRL_HOLD_FRAMES  64

/* The twist sweeps between BMAGIC_SWIRL_TWIST_MIN and BMAGIC_SWIRL_TWIST_MAX by BMAGIC_SWIRL_TWIST_STEP per frame. */
#define BMAGIC_SWIRL_TWIST_STEP   8
#define BMAGIC_SWIRL_TWIST_MAX    0x80
#define BMAGIC_SWIRL_TWIST_MIN    (-0x7F)

/* The swirl reads its texture back from here: the screen copy of the swirled square. */
#define BMAGIC_SWIRL_TEXTURE_X    832
#define BMAGIC_SWIRL_TEXTURE_Y    256

/* The swirl mesh: a band of BMAGIC_SWIRL_SEGMENTS quads between each two of BMAGIC_SWIRL_RINGS + 1 rings. */
#define BMAGIC_SWIRL_RINGS        8
#define BMAGIC_SWIRL_SEGMENTS     16
/* Masks a segment index back onto the ring. */
#define BMAGIC_SWIRL_WRAP         (BMAGIC_SWIRL_SEGMENTS - 1)

extern Magic010Steps D_801EEC04;

/* func_801EF0F8 */
void BMagic_SwirlDraw(s32 twist);

/* The screen point the swirl starts from, by g_Battle.scroll_dir. */
extern Offset2 g_BMagicSwirlStartPoints[];

/* BMagic_SwirlDraw's points: the outer and inner edge of the band being drawn, and the texture offsets of the mesh. */
extern Offset2 g_BMagicSwirlOuter[BMAGIC_SWIRL_SEGMENTS];
extern Offset2 g_BMagicSwirlInner[BMAGIC_SWIRL_SEGMENTS];
extern Offset2 g_BMagicSwirlTexOffsets[BMAGIC_SWIRL_RINGS + 1][BMAGIC_SWIRL_SEGMENTS];

#endif
