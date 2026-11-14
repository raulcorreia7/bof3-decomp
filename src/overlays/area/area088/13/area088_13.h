#ifndef OVERLAY_WORLD02_AREA088_13_H
#define OVERLAY_WORLD02_AREA088_13_H

/* The world02/area088/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern SVECTOR  D_1F800014[];
extern u8       D_801F58DC[];
extern u8       D_801F5900[];
extern u8       D_801F5902[];
extern u8       D_801F591C[];
extern u8       D_801F591D[];
extern Callback D_801F61A0[];
extern Callback D_801F61B4[];
extern Callback D_801F61BC[];
extern Callback D_801F61CC[];
extern u8       D_801F61DC[];
#define AREA_HUD_SPRITE_CELLS D_801F61DC
extern u8       D_801F61DD[];
extern u8       D_801F61DE[];
extern u8       D_801F61DF[];
extern Callback D_801F624C[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
/* D_801F6258 */
extern Point2u g_FlockVelocity[4];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
/* D_801F6268 */
extern u8       g_FlockScript[4][2];
extern Callback D_801F6270[];

void func_801F402C(void);
/* func_801F411C */
void Area_Update(void);
void func_801F41F0(void);
/* func_801F4664 */

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F6234[6];
#define AREA_HUD_MASK_TABLE D_801F6234

extern u16 D_800E4B3E;
/* g_SceneEventStep read unsigned: Fishing_ShowLocation steps it with a byte load. */
extern u8  g_SceneEventStep_u8[];
/* Key rows: column 0 is matched against g_GameContextSeed; column g_SceneState is the message Fishing_ShowLocation
 * starts. */
extern u16 D_801F6090[7][16];
/* Three fishing spots of 12 bytes: the spot id, then the 11 fish ids its board lists (0xFF ends the list). */
extern u8  D_801F6170[36];
extern u8  D_801F6194[]; /* the "Manillo" text at +0x10 */

void func_801F2F28(u8* window);

void func_801F3258(u8* window);

extern u8 D_801F6171[];

#include "overlays/area/world_cloud.h"

#endif
