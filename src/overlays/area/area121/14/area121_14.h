#ifndef OVERLAY_WORLD03_AREA121_14_H
#define OVERLAY_WORLD03_AREA121_14_H

/* The world03/area121/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "sys/actor.h"
#include "overlays/area/worlds/world03.h"
#include <rand.h>

/* The world-map entry keys WORLD_MAP_SELECT_KEY_SCRIPT scans. */
extern WorldMapKey D_801F64D8[4];
extern u8          D_801F64E8[];
extern u8          D_801F64E9[]; /* the y byte of each D_801F64E8 row */
/* The area ids the message step looks the current area up in. */
extern u16         D_801F67BC[4];
extern Callback    D_801F67C4[];
extern Callback    D_801F67D8[];
extern Callback    D_801F67E0[];
extern Callback    D_801F67F0[];
extern u8          D_801F6800[]; /* one four-byte sprite cell per id: w, h, u0, v0 */
#define AREA_HUD_SPRITE_CELLS D_801F6800
extern WorldMapMarker D_801F6858[6];
#define AREA_HUD_MASK_TABLE D_801F6858

/* The two 2-byte cells of the torch gauge bar texture. */
extern TorchGaugeCells D_801F2C04;
extern Callback        D_801F6870[];
extern Callback        D_801F6894[];
extern Callback        D_801F689C[];

/* sig-kept: the retail walk step tests the result unextended; the engine's s8 return adds an sll/sra. */
s32 func_801A79A4(s32 handler_x, s32 handler_y);

/* func_801F35D0 */
void Area_Update(void);
u8   func_801F5028(s32 x, s32 y, u8 dir);
void func_801F5380(void);
void func_801F595C(s32 value, s32 flag);

void func_801F5B90(void);

void func_801F5C7C(void);

#define AREA_TURN_SYNC func_801F5C7C

void func_801F4B4C(s32 input);
void func_801F60F4(void* actor);

extern u8 D_801F68B8[];

#endif
