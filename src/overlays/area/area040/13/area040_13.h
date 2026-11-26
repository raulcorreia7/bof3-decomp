#ifndef OVERLAY_WORLD01_AREA040_13_H
#define OVERLAY_WORLD01_AREA040_13_H

/* The world01/area040/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "game/spawn.h"
#include "overlays/area/worlds/world01.h"

/* The bundle record's command tag: the high byte of its first word. The
 * palette records the grid probe tests carry tags 0x23 to 0x25. */
#define BUNDLE_COMMAND_MASK (0xFF << 24)
#define BUNDLE_COMMAND(tag) ((tag) << 24)

/* The game-overlay state bytes the cancel path resets. */

extern u8 D_80144EA8[];
extern u8 D_80144EA9;
extern s8 D_80181B00[][2];
s32       func_801F2E78(void);

/* The 4x4 cell palette func_801F3570 tests each cell's value against. */
extern u8 D_801F4960[4][4];
extern u8 D_801F4970[];

/* The event's lookup table of pad-direction overrides, indexed by the held pad's top nibble. */
extern u8 D_801F4984[];

s32  func_801F3570(void);
void func_801F369C(void);
void func_801F372C(s32 pos0, s32 pos1);
void func_801F37D4(void);
void func_801A4BC0(s32 x, s32 y, s32 value);
s32  func_801F30B8(s32 x, s32 y);

#endif
