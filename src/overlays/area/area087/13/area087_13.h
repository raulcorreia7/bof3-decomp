#ifndef OVERLAY_WORLD02_AREA087_13_H
#define OVERLAY_WORLD02_AREA087_13_H

/* The world02/area087/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

/* The world-map entry keys WORLD_MAP_SELECT_KEY_SCRIPT scans. */
extern WorldMapKey D_801F4DAC[10];
extern u8          D_801F4DD4[2626];
extern u8          D_801F4DD5[];
extern Callback    D_801F5734[];
extern Callback    D_801F5748[];
extern Callback    D_801F5760[];
extern u8          D_801F5770[];
#define AREA_HUD_SPRITE_CELLS D_801F5770
extern u8       D_801F5771[];
extern u8       D_801F5772[];
extern u8       D_801F5773[];
extern Callback D_801F57E0[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
/* D_801F57EC */
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
/* D_801F57FC */

void func_801F34FC(void);
/* func_801F35EC */
void Area_Update(void);
void func_801F36C0(void);
/* func_801F3B34 */

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F57C8[6];
#define AREA_HUD_MASK_TABLE D_801F57C8

extern u16 D_801F55D8[9][16];
extern u8  D_801F5718[28];
extern u8  D_801F5719[]; /* the record-selector byte at +1 */
extern u8  D_801F5728[]; /* the "Manillo" text at +0x10 */

#include "overlays/area/shared/world_cloud.h"

#endif
