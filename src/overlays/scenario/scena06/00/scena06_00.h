#ifndef OVERLAY_SCENARIO_SCENA06_00_H
#define OVERLAY_SCENARIO_SCENA06_00_H

/* The scenario/scena06/00 overlay's local declarations. Only this image
 * includes the file. */

#include "engine/slus/slus.h"
#include "overlays/scenario/scenario.h"
#include "sys/exe.h"

extern u8  D_80144DF2;
extern u8  D_80144DF5;
extern u16 D_80144DF8;
extern u16 D_80144E00;

void func_801FD29C(void);

extern u16 D_80144E04;

extern u16 D_80144E06;
extern u16 D_80144E08;
extern u16 D_80144E0A;
extern u16 D_80144E20;
extern u16 D_80144E24;

extern u16                   D_80144E26;
extern u16                   D_80144E28;
extern u16                   D_80144E2A;
extern u16                   D_80146258;
extern u8                    D_8018E244;
extern u32                   D_801F6C00;
extern u8                    D_801FE3BC[];
extern Callback              D_801FE3D8[];
extern Callback              D_801FE3E4[];
/* D_801FE42C */
extern u8                    D_801FE464[8];
extern ActorMovementCallback D_801FE46C[];

extern u8 D_801FE478;
extern s8 (*D_801FE48C[])(void);
extern u8 D_801FE4E4;
extern u8 D_801FE4EC[];

#endif
