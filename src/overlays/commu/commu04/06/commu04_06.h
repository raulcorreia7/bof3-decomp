#ifndef OVERLAY_ETC_COMMU04_06_H
#define OVERLAY_ETC_COMMU04_06_H

/* The etc/commu04/06 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* g_EmiOverlayHeader */
/* Entries of the handler tables. */
#define COMMU04_STEP_COUNT  2
#define COMMU04_STEP0_COUNT 7

/* The item id table of each inventory category; the picker reads the job's category. */
extern u8*             g_ItemCategoryIds[];
/* D_801D1750 */
extern Callback        g_Commu04Steps[COMMU04_STEP_COUNT];
/* D_801D1758 */
extern Callback        g_Commu04Step0Steps[COMMU04_STEP0_COUNT];
extern u8              D_801D1774;
extern MenuChoicePanel g_Commu04ItemPanel; /* g_UIPanelTasks[0] */

/* The overlay's state byte the guarded step advances. */

void func_801D16A4(void);

#endif
