#ifndef OVERLAY_WORLD00_AREA026_13_H
#define OVERLAY_WORLD00_AREA026_13_H

/* The area026 world overlay's local declarations: the 0x40-byte world work
 * record, its handler table and prototypes. Only this image includes the
 * file. */

#include "overlays/area/world00.h"

extern u8 D_801F341C[6336];
extern u8 D_801F4CE4;

/* func_801650B4 */
bool Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
void func_801F2C94(void);
void func_801F2D5C(const s32* center, s32 radius);
void func_801F2E04(const s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y);
void func_801F300C(void);
void func_801F30D4(void);
void func_801F30FC(void);
void func_801F3124(void);
void func_801F3174(void);
void func_801F319C(void);
void func_801F31C4(void);
/* func_801F3230 */
void Area_SubViewOffsetY20(void);
/* func_801F3258 */
void Area_AddViewOffsetY20(void);
void func_801F3280(void);
void func_801F32B8(void);
void func_801F3338(void);

#endif
