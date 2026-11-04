#ifndef OVERLAY_ETC_COMMU03_06_H
#define OVERLAY_ETC_COMMU03_06_H

/* The etc/commu03/06 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* The overlay's step and sub-step handler pools; the tables are views into one
 * callback run, so the counts stay open until a data pass proves each range. */
extern Callback      D_801D18C8[];
extern Callback      D_801D18D4[];
extern Callback      D_801D18DC[];
extern Callback      D_801D18E4[];
extern u8            D_801D1948;
extern u8            D_801D1944;

/* The overlay's state byte the guarded step advances. */
#endif
