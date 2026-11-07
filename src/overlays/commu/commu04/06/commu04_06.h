#ifndef OVERLAY_ETC_COMMU04_06_H
#define OVERLAY_ETC_COMMU04_06_H

/* The etc/commu04/06 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* Entries of the handler tables. */
#define COMMU04_STEP_COUNT  2
#define COMMU04_STEP0_COUNT 7

/* D_801D1750 */
extern Callback g_Commu04StepFuncs[COMMU04_STEP_COUNT];
/* D_801D1758 */
extern Callback g_Commu04Step0Funcs[COMMU04_STEP0_COUNT];
extern u8       D_801D1774;

/* The overlay's state byte the guarded step advances. */

void func_801D16A4(void);

#endif
