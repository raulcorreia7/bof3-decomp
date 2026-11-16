#ifndef OVERLAY_ETC_COMMU04_06_H
#define OVERLAY_ETC_COMMU04_06_H

/* The etc/commu04/06 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* The copy shop's item choice prompts. */
#define FAIRY_MESSAGE_COPY_DECLINED       0x5F
#define FAIRY_MESSAGE_COPY_PICK_ITEM      0x60
#define FAIRY_MESSAGE_COPY_CONFIRM_ITEM   0x61
#define FAIRY_MESSAGE_COPY_CHOOSE_ANOTHER 0x63

/* g_EmiOverlayHeader */
/* Entries of the handler tables. */
#define COMMU04_STEP_COUNT                2
#define COMMU04_STEP0_COUNT               7

/* D_801D1750 */
extern Callback g_Commu04States[COMMU04_STEP_COUNT];
/* D_801D1758 */
extern Callback g_Commu04Step0Funcs[COMMU04_STEP0_COUNT];
extern u8       D_801D1774;

/* The overlay's state byte the guarded step advances. */

void func_801D16A4(void);

#endif
