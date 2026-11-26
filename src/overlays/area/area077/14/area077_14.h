#ifndef OVERLAY_WORLD02_AREA077_14_H
#define OVERLAY_WORLD02_AREA077_14_H

/* The world02/area077/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

/* The shared area.h gives this symbol no arguments; this image's function reads two. */
#define func_801F31EC Area_SharedVoidProto
#include "overlays/area/worlds/world02.h"
#undef func_801F31EC

#include "area/effects.h"

#define AREA_SPIN_RADIUS     32
#define AREA_SPIN_PITCH      RANDOM_MASK(0x3FF)
#define AREA_SPIN_SCALE_MASK 0xf
#define AREA_SPIN_SCALE_BASE 1
#define AREA_SPIN_FADE       0
/* The spin quad's sprite word: Area_ApplyTileToQuad reads tile 0x33 in selector 2's
 * table A, the 0x80 neutral colour byte and clut row 0x1E4. */
#define AREA_SPIN_QUAD_WORD  ((0x2180u << 16) | 0x0133u)

/* The four corner vectors RotTransPers4 projects; g_ScratchPadVectors forwards. */
extern s16      D_800E4800;
extern u16      D_800E5500;
extern u8       D_800E5502;
/* Main-RAM flag bank whose bit 0x2C gates the trigger search, and the scene mode byte
 * the trigger records are matched against. */
extern u8       D_80144EB8[];
extern WorldPos D_80146954;

/* One of the 64 slots at AREA_WORK, 0x34 bytes each: the trail centre, its two
 * ribbon edges and the rotation angle. */
typedef struct AreaSlot {
    Pos3   pos;      /* 0x00 - the trail centre */
    s32    unk_0C;   /* 0x0C */
    VECTOR edges[2]; /* 0x10, 0x20 - the ribbon's two edges */
    u16    angle;    /* 0x30 */
    u16    pad_32;   /* 0x32 */
} AreaSlot;

ASSERT_SIZE(AreaSlot, 0x34);

#define AREA_SLOT_COUNT 64

extern u8  D_801F6250[];
extern u8  D_801F6278[];
extern u8  D_801F627D[];
extern u8  D_801F6298[];
extern u8  D_801F62A0[];
extern u8  D_801F62EC[];
/* The two 4-byte trigger records, one byte view per field so each read keeps its
 * own address pair: the cell x and y, the scene mode byte and the flag id to toggle. */
extern u8  D_801F6B14[];
extern u8  D_801F6B15[];
extern u8  D_801F6B16[];
extern u8  D_801F6B17[];
extern u16 D_801F6B1C[];
extern u8  D_801F6B28[];
extern u8  D_801F6B30[];
extern u8  D_801F6B38[];
extern u8  D_801F6B40[];
extern u8  D_801F6B48[];
extern u8  D_801F6B50[];
extern u8  D_801F6B58[];
/* The twelve signed offset pairs the script row's entry byte selects. */
extern s8  D_801F6B60[][2];
extern u8  D_801F6B6C;
extern u8  D_801F6B70;
extern u8  D_801F6B74;

void       func_801F3778(u8 count, Pos2* current, RECT* rect);
/* func_801F3898 */
void       Area_DrawLine(Pos2 first, Pos2 second, u8 shade);
/* The two sprite tables the step draws index by the timer's low two bits. */
extern s32 D_801F62CC[];
extern s32 D_801F62DC[];
/* The spin-step draw reads six arguments from its two callers; the shared area.h cannot carry it
 * because three other images give func_801F35E0 no arguments. */
s16        func_801F35E0(s32 origin_x, s32 origin_y, s16 scroll_x, s16 scroll_y, s16 radius, s16 focus_x);
void       func_801F3CB8(void);
void       func_801F41B4(void);
void       func_801F3B48(Pos2* pos, u8 shade);
void       func_801F30E8(s16 x0, s16 y0, s16 x1, s16 y1);
void       func_801F3BC4(s16 x, s16 y, s16 w, s16 h);
void       func_801F31EC(s16 x, s16 y);

/* func_801F529C */
void Area_PaletteCopyRow(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);

/* The resident scenario dispatcher that runs the motion helper the scratchpad work byte 0x04 selects. */
s8 func_801FD34C(ScriptState* entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags);

extern void func_801F54B8(void);

void Actor_InitSlot(s32 type);
void func_801F462C(s32* pos, s16 radius, u8 center_shade, u8 rim_shade);

/* func_801F3198 */
void GFX_AddBlendDrawMode(u8 blend_mode);

#endif
