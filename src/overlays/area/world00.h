#ifndef WORLD00_FAMILY_H
#define WORLD00_FAMILY_H

/* Declarations shared by two or more world00 images; an image header that
 * reads one includes this file. */

#include "overlays/area/area.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT       0xFF
#define g_MasterSubStep          (*(s8*)&g_MasterSubStep)

/* The selection byte that arms the area request. */
extern s8 D_801490C7;
#include "overlays/area/Message_SelectAnswerValue.h"

void func_800F500C(void);
/* func_8014FF0C */
void UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);
void Area_SetCellCode(s16 column, s16 row, u8 code);
void Area_ProjectPoint(s32* pos, long* screen_xy);
void func_801E0C80(s32 graphic, s32 layer);
u8*  func_801E0DCC(s32 icon_index, s32 layer, s16 sprite_x, s16 sprite_y);
void Area_SpawnWeightedActor(void);
/* func_801F2C4C */
void Message_SelectAnswerValue(void);
void func_801F2D1C(void);
void func_801F3060(void);
void func_801F3360(void);
void func_801F36D0(void);

#endif
