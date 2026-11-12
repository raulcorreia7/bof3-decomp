#ifndef OVERLAY_BOSS_BOSS007_16_H
#define OVERLAY_BOSS_BOSS007_16_H

/* The boss/boss007/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8       D_800C1D78[];
extern u8       D_800C1D84[];
extern u16      D_800C1D90[];
extern u16      D_800C1D98[];
extern Callback D_800C1DA0[];
extern Callback D_800C1DD0[];
extern Callback D_800C1DDC[];
extern Callback D_800C1E0C[];
/* The text buffer SYS_CopyString fills with an ability name. */
extern s32      D_80149298;
/* The battle cell base at 0x80146390 is declared by src/overlays/battle/battle.h; this
 * overlay only clears the halfword at +0x4. */

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss007/16] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C18BC(s32 mode);
void func_800C19B4(s32 mode);

#endif
