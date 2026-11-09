#ifndef OVERLAY_WORLD00_AREA032_13_H
#define OVERLAY_WORLD00_AREA032_13_H

/* The area032 world overlay's local declarations. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/area/world00.h"
#include "area/spad.h"

extern SVECTOR  D_1F800014[];
extern u8       D_801468E4[];
extern Callback D_801F3F80[];

void Actor_TrackFocus(void);
void func_801F2DAC(void);
/* func_801F2E64 */
void Area_ShrinkDisc(void);
/* func_801F2EE4 */
void Scene_ClearActor(void);
void GFX_DrawShadedDisc(s16 x, s16 y, s16 radius, u8 center_shade, u8 rim_shade);
void func_801F30A8(void);
void func_801F30EC(void);
void Actor_Reveal(void);
/* func_801F35B4 */
void Actor_FreePaletteFades(void);
void func_801F363C(void);
/* func_801F36A0 */
void Message_Clear(void);
void func_801F36E4(void);
void func_801F3728(void);
void func_801F378C(void);
void func_801F3800(void);
void func_801F3844(void);
void func_801F3920(void);
void func_801F3C18(void);
void func_801F3DCC(void);

#endif
