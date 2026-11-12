#ifndef OVERLAY_ETC_COMMU05_07_H
#define OVERLAY_ETC_COMMU05_07_H

/* The etc/commu05/07 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* The overlay's step table: the handlers the entry stub dispatches, selected
 * by the commu step byte commu00 owns. */
#define COMMU05_STEP_COUNT 3

typedef struct {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s8 unk_04;
} Commu05State;

extern Commu05State D_801D19F0;

extern OverlayHeader D_801D0C00;
/* D_801D1950 */
extern Callback      g_Commu05States[COMMU05_STEP_COUNT];

/* The five-byte names of the fairy jobs the room list draws. */
extern u8   D_801457E8[];
/* "faeries" for several, "faery" for one, and the "%2d" count format. */
extern u8   D_801D195C[];
extern u8   D_801D1964[];
extern char D_801D0C0C[];

void func_801D0F50(s16 x, s16 y, s32 flags);

#endif
