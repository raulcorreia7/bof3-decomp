#ifndef OVERLAY_ETC_COMMU03_06_H
#define OVERLAY_ETC_COMMU03_06_H

/* The etc/commu03/06 overlay's local declarations. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* Entries of the handler tables. */
#define COMMU03_STEP_COUNT  3
#define COMMU03_STEP0_COUNT 2
#define COMMU03_STEP1_COUNT 2
#define COMMU03_STEP2_COUNT 4

/* D_801D18C8 */
extern Callback g_Commu03States[COMMU03_STEP_COUNT];
/* D_801D18D4 */
extern Callback g_Commu03Step0Funcs[COMMU03_STEP0_COUNT];
/* D_801D18DC */
extern Callback g_Commu03Step1Funcs[COMMU03_STEP1_COUNT];
/* D_801D18E4 */
extern Callback g_Commu03Step2Funcs[COMMU03_STEP2_COUNT];
extern u8       D_801D1944;
extern u8       D_801D1948;

/* The overlay's state byte the guarded step advances. */

void func_801D1250(s32 arg0, s32 arg1);

#endif
