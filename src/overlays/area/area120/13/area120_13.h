#ifndef OVERLAY_WORLD03_AREA120_13_H
#define OVERLAY_WORLD03_AREA120_13_H

/* The world03/area120/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "work/actor.h"
#include "overlays/area/world03.h"
#include "work/area_spad.h"

extern u8 D_801F43B8[];

/* The width and height halves of the RECT at the start of D_801F43B8. */
extern u16 D_801F43BC;
extern u16 D_801F43BE;

void func_801F35B8(void);
s32  func_801F36B0(void);

extern u8 D_801F43E4;

extern u16 D_801F4FD4;

/* The work window's rows: a byte table of 0x1C-byte rows. */
#define AREA_ROW_COUNT  0x100
#define AREA_ROW_STRIDE 0x1C

/* g_GameEntryState and the byte after it, read as one word. */
extern u32 g_GameEntryStateWord;

void func_801F3630(void);

void func_801F3F5C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif
