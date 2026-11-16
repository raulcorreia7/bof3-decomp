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

/* g_EmiOverlayHeader */
/* D_801D1950 */
extern Callback g_Commu05States[COMMU05_STEP_COUNT];

/* The entry rows of the shared executable's fairy list (D_80145E48) and the
 * 5-byte icon cells each row byte selects (D_801457E8). */
extern u8 D_80145E48[];
extern u8 D_801457E8[][5];

/* The background panel's cell origins, a u and a v byte per tile:
 * D_801D199C, D_801D19BC and D_801D19DC. */
extern u8 D_801D0C0C[];
extern u8 D_801D196C[];
extern u8 D_801D1974[];
extern u8 D_801D199C[][2];
extern u8 D_801D19BC[][2];
extern u8 D_801D19DC[][2];

#endif
