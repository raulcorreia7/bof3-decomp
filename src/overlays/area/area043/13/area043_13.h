#ifndef OVERLAY_WORLD01_AREA043_13_H
#define OVERLAY_WORLD01_AREA043_13_H

/* The world01/area043/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

/* func_8019651C */
s32  func_8019651C(u8* color_data, s32 palette_base, s32 palette_count, s32 palette_index, s32 flag_value);
/* func_80196718 */
void func_80196718(void* target);

extern u8 D_801F37F8[];

#endif
