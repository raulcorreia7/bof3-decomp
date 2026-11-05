#ifndef OVERLAY_WORLD01_AREA045_13_H
#define OVERLAY_WORLD01_AREA045_13_H

/* The world01/area045/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern SVECTOR     D_1F800014[];
extern s32         D_80145EC4[];
extern u8          D_801F4D7C[];
/* The spawn step handler table indexed by the record's step byte. */
extern Callback    D_801F5338[];
extern u8          D_801F534C[];
extern u8          D_801F5354[];
extern u8          D_801F53E4[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
extern ScreenPoint D_801F53F0[];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
extern u8          D_801F5400[];
extern u8          D_801F5401[];
extern u8          D_801F5408[];

/* The steppers that reload the cell after every store select the volatile
 * declaration. */

/* The value of func 801f2eec table in the shared func_801F2EEC body. */
#define FUNC_801F2EEC_TABLE D_801F5338

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP    Area_DrawHud

extern WorldMapMarker D_801F53CC[6];
#define AREA_HUD_MASK_TABLE D_801F53CC
/* func_801F3ECC */
void                  Area_DrawGradientDiamond(s16 x, s16 y);

/* func_801F39D8 */
void Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);

extern u8  D_801F4DA4[548];
extern u16 D_801F51BC[9][16];
extern u8  D_801F531C[28];
extern u8  D_801F531D[]; /* the record-selector byte at +1 */
extern u8  D_801F532C[]; /* the "Manillo" text at +0x10 */
void       Fish_LocationMessage(void);

void func_801F40C4(s16 x, s16 y);
void Area_Update(void);

#endif
