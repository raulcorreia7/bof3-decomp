#ifndef WORLD00_FAMILY_H
#define WORLD00_FAMILY_H

#include "overlays/area/area.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT       0xFF
#define g_MenuMasterSubStep      (*(s8*)&g_MenuMasterSubStep)

#include "overlays/area/Message_SelectAnswerValue.h"

void func_800F500C(void);
/* func_801E0C80 */
void Fishing_SetDrawMode(s32 graphic, s32 layer);
/* func_801E0DCC */
u8*  Fishing_DrawSprite(s32 icon_index, s32 layer, s16 sprite_x, s16 sprite_y);
/* func_801F2C4C */
void Message_SelectAnswerValue(void);
void func_801F2D1C(void);
void func_801F3060(void);
void func_801F3360(void);
void func_801F36D0(void);

#endif
