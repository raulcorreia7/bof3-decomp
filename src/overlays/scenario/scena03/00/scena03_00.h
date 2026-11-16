#ifndef OVERLAY_SCENARIO_SCENA03_00_H
#define OVERLAY_SCENARIO_SCENA03_00_H

/* The scenario/scena03/00 overlay's local declarations. Only this image
 * includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

/* The line record func_801F88FC draws at +0x0C of the task row: the radius and the two angles of
 * its direction, a scale and a colour multiplier for each end. */
typedef struct Scena03Line {
    s16       radius;      /* +0x00 */
    s16       yaw;         /* +0x02 */
    s16       pitch;       /* +0x04 */
    s16       start_scale; /* +0x06 */
    s16       end_scale;   /* +0x08 */
    ColorRGB8 color;       /* +0x0A */
} Scena03Line;

ASSERT_SIZE(Scena03Line, 0x0E);
ASSERT_OFFSET(Scena03Line, start_scale, 0x06);
ASSERT_OFFSET(Scena03Line, color, 0x0A);

/* The head of the task row this scene reads as its line record. */
typedef struct Scena03Work {
    u8          pad_00[0x0C];
    Scena03Line line; /* +0x0C */
} Scena03Work;

ASSERT_SIZE(Scena03Work, 0x1A);
ASSERT_OFFSET(Scena03Work, line, 0x0C);

#define SCN_LINE ((Scena03Work*)g_Task)

/* The four corner points of a quad that func_801F7FFC places around a centre: each is the centre plus a
 * rotated offset. */
typedef struct Scena03Corner {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
} Scena03Corner;

typedef struct Scena03Quad {
    s32           x;          /* +0x00 centre */
    s32           y;          /* +0x04 */
    s32           z;          /* +0x08 */
    Scena03Corner corner[4];  /* +0x0C */
    s16           angle;      /* +0x4C offset direction */
    s16           rotation_y; /* +0x4E */
    s16           rotation_z; /* +0x50 */
    s16           length;     /* +0x52 offset length */
} Scena03Quad;

ASSERT_SIZE(Scena03Quad, 0x54);
ASSERT_OFFSET(Scena03Quad, corner, 0x0C);
ASSERT_OFFSET(Scena03Quad, angle, 0x4C);
ASSERT_OFFSET(Scena03Quad, length, 0x52);

/* g_ScratchPadVectors */
extern SVECTOR  g_ScratchPadVectors[];
extern s16      D_801492DA;
extern s8       D_80144EA0;
extern u8       D_801468E4[];
extern u32      D_801F6C00;
/* D_801FCF24 */
extern u8       D_801FCF30[];
extern s16      D_801FCF40;
extern s16      D_801FCF42;
extern Callback D_801FCF50[];
extern u8       D_801FCF5C[];
extern Callback D_801FCF70[];
extern Callback D_801FCF88[];
extern Callback D_801FCF94[];
extern Callback D_801FCFA0[];
extern Callback D_801FCFAC[];
extern Callback D_801FCFD4[];
extern Callback D_801FCFE0[];

/* D_801FD00C */

s32 func_801FC5A4(void);

/* Sets one scene flag bit, then runs func_801FC5A4. */
static inline void Scene_SetFlagThenContinue(void* flags, u8 bit) {
    SYS_SetFlag(flags, bit);
    func_801FC5A4();
}

extern u8 D_80143F03;
extern u8 D_80144EA2;
extern u8 D_80144F5B;
extern u8 D_80144F5C;
extern u8 D_80144F5F;

s32 func_8019601C();

extern u16      D_80146876;
extern u16      D_8014600E;
extern u16      D_80146258;
extern s8       D_801FD004[4];
extern s8       D_801FD008[2];
extern u8       D_801FD030;
extern Callback D_801FD038[];

/* The camera nudges of 270.c: step the scroll words by the table entry picked with the low bits of the facing counter. They differ only in table and mask. */
#define SCENA03_NUDGE_SCROLL(table, mask) \
    do {                                  \
        u16* scroll;                      \
        u16  dir;                         \
                                          \
        dir    = D_80146876 & (mask);     \
        scroll = (u16*)&D_80145ECE;       \
        *scroll += (table)[dir] * 16;     \
        D_8014600E += (table)[dir] * 16;  \
    } while (0)

s8 func_801FCD1C(s32 x, s32 y);

void func_801F8170(s32* vertices);
void func_801F8200(s32* vertices, s32 v0, s32 v1, s32 v2);

void func_801F88FC(Scena03Line* line);

void func_801F7FFC(Scena03Quad* quad);

/* The area probes func_801FC704 dispatches to: each tests the entry coordinates against the cells
 * of its area. */
s32 func_801FC7EC(s32 entry_x, s32 entry_y);
s32 func_801FC8AC(s32 entry_x, s32 entry_y);
s8  func_801FC944(s32 entry_x, s32 entry_y);
s8  func_801FC9DC(s32 entry_x, s32 entry_y);
s8  func_801FCAB8(s32 entry_x, s32 entry_y);
s8  func_801FCB4C(s32 entry_x, s32 entry_y);

#endif
