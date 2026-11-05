#ifndef OVERLAY_WORLD01_AREA059_13_H
#define OVERLAY_WORLD01_AREA059_13_H

/* The world01/area059/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

/* The script copy points at an Actor row of g_Actors; the shared declaration
 * is a byte cursor, so this image views it as the record it addresses. */
#define g_ScriptWorkRecord ((Actor*)g_ScriptWorkRecord)

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_80146867;

extern u8 D_801F3824[];

/* func_80196718 */
void GFX_FreePaletteFadeTarget(void* target);
void func_801F30A8(s32* pos);

/* func_801F2E80 */
s32 Area_CheckStepTrigger(s32 x, s32 y);

/* The first row of the trigger band in the shared Area_CheckStepTrigger body. */
#define AREA_STEP_TRIGGER_ROW 0x29

#endif
