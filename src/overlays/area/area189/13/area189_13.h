#ifndef OVERLAY_WORLD04_AREA189_13_H
#define OVERLAY_WORLD04_AREA189_13_H

/* The world04/area189/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The scratchpad work row the entry paths read. */

/* The character work record, viewed as bytes here. */

/* The area-flag bit store and the global flag byte. */

/* The party row table and the row field the drain pass reads. */

/* The game-overlay state bytes the cancel paths reset. */

extern u16      D_801492DC;
/* The eight-direction unit step table: the x and y words of the entry, 1/16 of a tile per unit. */
extern Point2l D_801F6308[];
/* The per-buffer ordering-table heads, one 8-byte entry per slot. */
extern u32*     D_80143534[][2];
/* The key-state word and its mask partner (gameui.h names it g_InputPressed). */
/* The state handler banks the step dispatchers index. */
extern Callback D_801F6238[];
extern s8       D_801F6284[];
extern s8       D_801F6285[];

/* The image's step passes. */
void func_801F3514(void);
void func_801F3800(void);
s32  func_801F4A04(s32 x, s32 y);
void func_801F559C(void);
/* func_801F5F20 */
void Actor_ClearVelocity(void);
void func_801F5600(void);

extern Callback D_801F62F4[];

#endif
