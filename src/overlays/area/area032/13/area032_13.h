#ifndef OVERLAY_WORLD00_AREA032_13_H
#define OVERLAY_WORLD00_AREA032_13_H

/* The area032 world overlay's local declarations: the sprite and scratch views,
 * its handler table and prototypes. Only this image includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/area/world00.h"
#include "work/area_spad.h"
#include "work/save.h"

extern SVECTOR  D_1F800014[];
extern s32      D_80145EC4;
extern u8       D_801468E4[];
extern Callback D_801F3F80[];

void Actor_ProjectFocusAndStep(void);
void func_801F2DAC(void);
void func_801F2E64(void);
void func_801F2EE4(void);
void GFX_DrawShadedDisc(s16 x, s16 y, s16 radius, u8 center_shade, u8 rim_shade);
void func_801F30A8(void);
void func_801F30EC(void);
void Actor_UnhideAndFinishAtZero(void);
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
