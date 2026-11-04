#ifndef OVERLAY_ETC_COMMU04_06_H
#define OVERLAY_ETC_COMMU04_06_H

/* The etc/commu04/06 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* The overlay's step and sub-step handler pools; the tables are views into one
 * callback run, so the counts stay open until a data pass proves each range.
 * After the step, the entry redraws the menu panels while the game state is
 * still zero. */
extern Callback      D_801D1750[];
extern Callback      D_801D1758[];
extern u8            D_801D1774;

/* The overlay's state byte the guarded step advances. */
#endif
