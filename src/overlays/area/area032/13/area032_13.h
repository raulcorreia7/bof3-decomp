#ifndef OVERLAY_WORLD00_AREA032_13_H
#define OVERLAY_WORLD00_AREA032_13_H

/* The area032 world overlay's local declarations: the sprite and scratch views,
 * its handler table and prototypes. Only this image includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/area/world00.h"
#include "area/spad.h"

extern SVECTOR  D_1F800014[];
extern u8       D_801468E4[];
extern Callback D_801F3F80[];

void func_801F2DAC(void);
/* func_801F2E64 */
void Area_ShrinkDisc(void);
/* func_801F2EE4 */
void func_801F30A8(void);
void func_801F30EC(void);
/* func_801F35B4 */
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

#endif
