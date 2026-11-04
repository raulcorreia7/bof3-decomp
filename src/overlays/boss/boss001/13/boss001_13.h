#ifndef OVERLAY_BOSS_BOSS001_13_H
#define OVERLAY_BOSS_BOSS001_13_H

/* The boss/boss001/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

extern u8           D_800C217C[];
extern u8           D_800C2194[];
extern u16          D_800C21AC[];
extern u16          D_800C21B4[];
extern Callback     D_800C21EC[];
extern Callback     D_800C2204[];
extern Callback     D_800C2210[];
extern Callback     D_800C221C[];
extern Callback     D_800C224C[];
extern Callback     D_800C2264[];
extern Callback     D_800C2270[];
/* Battle RAM cell cleared by the mode start; the block around it belongs to
 * include/battle/ram.h, which does not name this halfword yet. */
extern volatile u16 D_801463BE;
extern u8           D_800C2188;

/* The three battle hooks the image installs; the addresses are in
 * [emi/boss/boss001/13] of config/symbols.toml. */

/* The enemy-work mode dispatch each installer publishes at unk_E4. */
void func_800C1E00(s32 mode);

#endif
