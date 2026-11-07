#ifndef OVERLAY_ETC_COMMU01_07_H
#define OVERLAY_ETC_COMMU01_07_H

/* The etc/commu01/07 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* Entries of the handler tables. */
#define COMMU01_STEP_COUNT       3
#define COMMU01_STEP2_COUNT      3
#define COMMU01_STEP2_SUB1_COUNT 6

/* D_801D4BCC */
extern Callback g_Commu01States[COMMU01_STEP_COUNT];
/* D_801D4BD8 */
extern Callback g_Commu01Step2Funcs[COMMU01_STEP2_COUNT];
extern Callback D_801D4BE4[];
/* D_801D4BEC */
extern Callback g_Commu01Step2Sub1Funcs[COMMU01_STEP2_SUB1_COUNT];
extern u8       D_801D4DF4;
extern u8       D_801D4DF8;
extern u8       D_801D4DFC;

extern u8  D_801D4E00;
extern u8  D_801D4E04;
extern u8  D_801D4E08;
extern u16 D_801D4E0C;

extern u8  D_801D4E10;
extern u16 D_801D4E14;
extern u8  D_801D4E18;

#endif
