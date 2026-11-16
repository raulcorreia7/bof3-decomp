#ifndef OVERLAY_SCENARIO_SCENA17_00_H
#define OVERLAY_SCENARIO_SCENA17_00_H

/* The scenario/scena17/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

void            Shop_DispatchStep(void);
extern u8       D_80143BB4;
extern s8       D_80146873;
extern u32      D_801F6C00;
extern Callback D_801F973C[];
extern Callback D_801F9748[];

/* sig-kept: the callee masks semi to u8; an s32 parameter keeps GCC 2.7.2's prologue copy order. */
void            func_801F88CC(s32 semi, s32 color);
void            func_801F8B10(s32 arg0, s32 arg1);
void            func_801F8EF0(void);
void            func_801F8FAC(s32 x, s32 y, s32 color, u8 semi_trans);
/* func_801F91F0 */
void            Scene_DrawEndingRollLine(s16 x, s16 y, u8* text);
/* func_801F938C */
bool            Scene_UpdateEndingRoll(void);
/* D_801F97DC */
extern u8       g_EndingGlyphWidth[];
/* D_801F981C */
extern u8*      g_EndingRollText[];
/* func_801F9490 */
void            Scene_RunSaveMenu(void);
extern Callback D_801F9758[];

extern Callback D_801F9798[];

extern Callback D_801F97A4[];
/* D_801F97D8 */
extern Callback D_801F9DBC[];
/* D_801F9DD0 */
extern u16      g_EndingRollLine;
/* D_801F9DD4 */
extern u8       g_EndingRollScroll;
extern u8       D_801F9DD8;

#endif
