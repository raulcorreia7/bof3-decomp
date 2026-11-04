#ifndef OVERLAY_WORLD04_AREA197_13_H
#define OVERLAY_WORLD04_AREA197_13_H

/* The world04/area197/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

/* The scratchpad work row and the published record the step paths read. */

/* The character work record, viewed as bytes here. */

/* The area-flag bit store. */
extern u8                  D_80144EF8[];
/* The state handler banks the step dispatchers index. */
extern u8                  D_801F431C[];
extern Callback            D_801F4368[];
/* D_801F4A2C */
extern PartyMemberMessages g_PartyMemberMessages[7];
extern Callback            D_801F4A80[];
/* The two-byte step table the falling path indexes. */
extern s8                  D_801F4A88[];
extern s8                  D_80146874;
extern s8                  D_80146875;

/* The image's step passes. */
void func_801F3768(s32 arg0, s32 arg1);

#endif
