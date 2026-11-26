#ifndef SYSTEM_SCRATCHPAD_H
#define SYSTEM_SCRATCHPAD_H

/* The PlayStation scratchpad, 1 KiB. Every overlay stages its current work in the base cells and
 * leaves its task in the cell at 0x44; the loader streams through the tail. */

#include "common/vector.h"
#include "psx/mem.h"
#include "psx/psyq.h"
#include "types.h"

/* The sparkle ray: the screen point it leaves, the sweep angle of its rays and the shade they fade
 * to. A reading of ScratchPad.cells.halves. */
typedef struct ScratchPadRay {
    u16        x; /* 0x00 */
    u16        y; /* 0x02 */
    u8         pad_04[2];
    s16        angle; /* 0x06 */
    ColorRGB16 shade; /* 0x08 */
} ScratchPadRay;

#define SCRATCH_PAD_RAY_SIZE 0x0E
ASSERT_OFFSET(ScratchPadRay, angle, 0x06);
ASSERT_OFFSET(ScratchPadRay, shade, 0x08);
ASSERT_SIZE(ScratchPadRay, SCRATCH_PAD_RAY_SIZE);

/* The 16 bytes at the base, read at three widths: the entity slot the area and scene code stages in
 * byte 0 (the battle event slot in bytes 0-2), the halfword counters and effect parameters, and the
 * scene math scratch words. */
typedef union ScratchPadCells {
    u8            bytes[16]; /* 0x00 */
    s16           halves[8]; /* 0x00 */
    s32           words[4];  /* 0x00 */
    ScratchPadRay ray;       /* 0x00 */
} ScratchPadCells;

#define SCRATCH_PAD_CELLS_SIZE 0x10
ASSERT_SIZE(ScratchPadCells, SCRATCH_PAD_CELLS_SIZE);

/* One scratchpad object for every mode: the base cells, the halfword-pointer cell a
 * draw pass walks, the four RotTransPers4 corner vectors, and the cell each overlay leaves its task
 * in. */
typedef struct ScratchPad {
    /* 0x000 */ ScratchPadCells cells;
    /* 0x010 */ s16*            unk_10; /* the pointer cell a scene or draw pass walks */
    /* 0x014 */ SVECTOR         vectors[4];
    /* 0x034 */ s16             unk_34[2];
    /* 0x038 */ s16             unk_38; /* the area emit pair extent */
    /* 0x03A */ s16             unk_3A; /* the area emit pair mode */
    /* 0x03C */ u8              unk_3C[8];
    /* 0x044 */ struct Self*    task;
    /* 0x048 */ u8              unk_48[0x3B8];
} ScratchPad;

ASSERT_OFFSET(ScratchPad, cells, 0x000);
ASSERT_OFFSET(ScratchPad, unk_10, 0x010);
ASSERT_OFFSET(ScratchPad, vectors, 0x014);
ASSERT_OFFSET(ScratchPad, unk_34, 0x034);
ASSERT_OFFSET(ScratchPad, unk_38, 0x038);
ASSERT_OFFSET(ScratchPad, unk_3A, 0x03A);
ASSERT_OFFSET(ScratchPad, unk_3C, 0x03C);
ASSERT_OFFSET(ScratchPad, task, 0x044);
ASSERT_OFFSET(ScratchPad, unk_48, 0x048);
ASSERT_SIZE(ScratchPad, SCRATCH_PAD_SIZE);

/* The scratchpad as a typed object at a byte offset: SPAD(0u)->cells.bytes[0]. The existing
 * SCRATCH_PAD/SP/SP_PTR/SP_REF helpers in psx/mem.h keep working. */
#define SPAD(byte_offset) SP_PTR(ScratchPad, byte_offset)

/* ScratchPad.vectors as the symbol the area, bmagic and scenario code names directly. */
/* g_ScratchPadVectors */
extern SVECTOR g_ScratchPadVectors[4];
/* The same four vectors read a halfword at a time. */
extern s16     g_ScratchPadVectorHalves[];

/* Advance the triangle fan on the scratchpad one step: vertex 0 stays at the origin, vertex 1 takes
 * the old rim point and vertex 2 moves to the rim point at `angle`, `radius` away. */
#define GFX_STEP_TRIANGLE_FAN(angle, radius)                      \
    g_ScratchPadVectors[0].vx = 0;                                \
    g_ScratchPadVectors[0].vy = 0;                                \
    g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;        \
    g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;        \
    g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(angle), (radius)); \
    g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(angle), (radius))

/* Scratchpad base + 1; battle/battle/03 and etc/game/00 write it directly. */
extern u8  D_1F800001;
/* ScratchPad.cells.halves[3]: the staged y coordinate that func_801B13BC writes, and the phase angle
 * the KaiserBreath steps store before rcos loads it back. */
extern s16 D_1F800006;
extern s16 D_1F800016;
extern s16 D_1F800018;
extern s16 D_1F800034[2];
/* ScratchPad.unk_38/unk_3A: the area emit pair extent and its mode. */
extern s16 D_1F800038;
extern s16 D_1F80003A;

#endif
