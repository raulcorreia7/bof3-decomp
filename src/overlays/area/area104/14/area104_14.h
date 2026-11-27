#ifndef OVERLAY_WORLD02_AREA104_14_H
#define OVERLAY_WORLD02_AREA104_14_H

/* The world02/area104/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

void func_801F358C(void);

/* The arrow cell of each torch gauge state. */
extern TorchGaugeCells D_801F2C04;
extern u8              D_801F2C08[];
/* The world-map entry keys WORLD_MAP_SELECT_KEY_SCRIPT scans. */
extern WorldMapKey     D_801F6980[1];
extern u8              D_801F6984[];
extern Callback        D_801F6A64[];
extern u8              D_801F6A78[];
extern u8              D_801F6A80[];
extern u8              D_801F6A90[];

/* The map arrow sprite's width, height, u and v per sprite id. */
extern u8 D_801F6AA0[];
#define AREA_HUD_SPRITE_CELLS D_801F6AA0
/* The word the torch flame's palette swap writes each eighth frame. */
extern u16 D_800396C6;
extern u8  D_801F6B10[];
extern u8  D_801F6B18[];

/* The three x then three y corners of each of the four triangles the torch flame draws. */
extern u16 D_801F6B2C[][6];

/* func_801F367C */
void Area_Update(void);
/* func_801F3BC4 */
void func_801F4E3C(void);
void func_801F5418(s32 value, s32 flag);
void func_801F555C(s16 x, s16 y, u8 row);
void func_801F564C(void);
void func_801F5738(void);

#define AREA_TURN_SYNC       func_801F5738
#define AREA_MESSAGE_REQUEST 4 /* the message UI_MessageRunArea starts */

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F6AF8[6];
#define AREA_HUD_MASK_TABLE D_801F6AF8

/* sig-kept: the retail walk step tests the result unextended; the engine's s8 return adds an sll/sra. */
s32 func_801A79A4(s32 handler_x, s32 handler_y);

u8         func_801F4AE4(s32, s32, s32);
/* The area CLUT: the first 32 entries of the palette mirror at GAME_PALETTE_MIRROR. */
extern u16 D_800396C0[];

/* The transfer queue's row and window tables (GFX_UpdateTransferQueue). */
extern u16 D_80145A54[];
/* The area overlay code base (AreaHandlerRecord.code_base), the engine's AREA_CODE_BASE. */
#define AREA_CODE_BASE ((0x800Fu << 16) | 0x5000u)

void func_801F4608(s32 input);
void func_801F5BB0(s32 actor);

void func_801F656C(void);
s32  func_801F66D0(s16 cell_x, s16 cell_y);

extern const BGMTrack g_BGMTracks[BGM_TRACK_COUNT];

#endif
