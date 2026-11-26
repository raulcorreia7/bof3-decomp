#ifndef OVERLAY_WORLD04_AREA189_13_H
#define OVERLAY_WORLD04_AREA189_13_H

/* The world04/area189/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"
/* The scratchpad work row the entry paths read. */
extern s8*  D_1F800010;
/* The cell ordering-table rows: six 8-byte lists per grid row, head then tail. */
extern u8   D_80142CC0[];
/* The per-buffer ordering-table heads, one 8-byte entry per slot. */
extern u32* D_80143534[][2];

/* The marker screen-y source flag and the y it holds. */
extern s16 D_80145EC0;

/* The character work record, viewed as bytes here. */

/* The area-flag bit store and the global flag byte. */
/* Steps until the next encounter, rolled by Area_EncounterRollThreshold. */
extern u16 D_80145FB8;
/* The sorted object pointer list and its count. */
/* D_8014828C */
extern s32 g_AreaGridActors[];

/* The party row table and the row field the drain pass reads. */

/* The game-overlay state bytes the cancel paths reset. */

extern u16 D_801492DC;

/* The camera view rotation the refresh compares against. */
extern SVECTOR  D_801492E0;
/* The number of words in the cell packet list. */
extern u8       g_AreaCellPacketCount;
/* The eight facing rows of the band scan: origin, column and row steps. */
extern u8       D_801F6108[];
/* The 16 x 16 block table the height query maps a cell to. */
extern u8       D_801F6138[];
/* The key-state word and its mask partner (gameui.h names it g_PadStates[0].pressed). */
/* The state handler banks the step dispatchers index. */
extern Callback D_801F6238[];
/* The x of the five edges between the four marker quads, and the bottom y at each edge. */
extern u16      D_801F6240[];
extern u8       D_801F624C[];
/* The palette tint triple per phase that func_801F3800 applies past phase 0x390. */
extern s8       D_801F6254[][3];
extern s8       D_801F6284[];
extern s8       D_801F6285[];
extern u8       D_801F62F0[];
/* The eight-direction unit step table: the x and y words of the entry, 1/16 of a tile per unit. */
extern Offset2  D_801F6308[];

/* The per-facing entry seeds: the area id and the entry tile's x and y high
 * halves, one byte each, plus the four facing jitters func_801F5D6C adds. */
extern u8 D_801F6388[];
extern u8 D_801F6389[];
extern u8 D_801F638A[];

/* The image's step passes. */
void func_801F2DE0(void);
void Area_CellSetTexture(s32 texture, POLY_FT4* prim);
void func_801F3514(void);
void func_801F3800(void);
void func_801F4150(s32 shade, s32 x);
void func_801F43E8(s32 scale);
void func_801F497C(u8 size);
s16  func_801F4A04(s32 x, s32 y);
void func_801F4B64(TILE_1* source);
void func_801F518C(void);
void func_801F54B0(void);
void func_801F559C(void);
/* func_801F5F20 */
void func_801F5600(void);
void func_801F5D20(void);
u8   func_801F5D6C(void);
bool func_801F5EA8(void);
s32  func_801F5F3C(void);
void Char_AddFatigue(void);
void func_801F6088(void);

extern Callback D_801F62F4[];

#endif
