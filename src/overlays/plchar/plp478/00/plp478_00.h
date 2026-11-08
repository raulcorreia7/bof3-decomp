#ifndef OVERLAY_PLCHAR_PLP478_00_H
#define OVERLAY_PLCHAR_PLP478_00_H

/* The plchar/plp478/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 20

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CF6D8[];
extern Callback D_801CF6E4[];
extern Callback D_801CF6F0[];
extern Callback D_801CF6FC[];
extern Callback D_801CF708[];
extern Callback D_801CF710[];
extern Callback D_801CF71C[];

/* LOGO.EXE is loaded independently, this call targets its reviewed entry address rather than linking LOGO.EXE into
 * SLUS_004.22 */
void func_801CE758(void);
#endif
