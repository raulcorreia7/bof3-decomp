#ifndef OVERLAY_WORLD03_AREA118_13_H
#define OVERLAY_WORLD03_AREA118_13_H

/* The world03/area118/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

extern u8  D_80144ED0[];
extern u8  D_801F511C[];
extern u8  D_801F5198[];
/* The cell coordinate byte pairs and the half distances of the slots the seed
 * step indexes: the pair at D_801F51B0[slot * 2], the half distance at D_801F51B4[slot]. */
extern u8  D_801F51B0[];
extern u8  D_801F51B1[];
extern u16 D_801F51B4[];
extern u8  D_801F59E0[];
extern u8  D_801F59E1[];
extern u8  D_801F59E2[];
extern u8  D_801F59E3[];
extern u16 D_801F59E4;
extern u8  D_801F59E8;
extern u8  D_801F59EC;
extern u8  D_801F5138[];
extern u8  D_801F5994[];
extern u8  D_801F5998[];
extern u8  D_801F5999[];
void       func_801F381C(s32 arg0);

void func_801F33A4(void);
void func_801F4634(s32, s32);

void func_801F4278(void);
void func_801F43FC(void);
void func_801F48E0(void);
void func_801F4CD0(void);
/* The work bound lookup of the party row's trigger box. */
u8   func_801F4C08(u8 member);
/* The resident field-step helpers the party sync calls. */
void func_801C2538(void);
void func_801C2710(void);

#endif
