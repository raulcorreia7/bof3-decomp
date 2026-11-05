#ifndef OVERLAY_ETC_COMMU01_07_H
#define OVERLAY_ETC_COMMU01_07_H

/* The etc/commu01/07 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* The overlay's step and sub-step handler pools. The tables overlap: each entry
 * stub starts at its own offset into the same run of callbacks, so the counts
 * stay open until a data pass proves each reader's range. */
extern Callback      D_801D4BCC[];
extern Callback      D_801D4BD8[];
extern Callback      D_801D4BE4[];
extern Callback      D_801D4BEC[];
extern u8            D_801D4E08;

extern u8  D_801D4DF4;
extern u8  D_801D4DF8;
extern u8  D_801D4DFC;
extern u16 D_801D4E0C;

extern u8  D_801D4E10;
extern u16 D_801D4E14;
extern u8  D_801D4E18;

#endif
