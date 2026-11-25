#ifndef OVERLAY_ETC_COMMU05_07_H
#define OVERLAY_ETC_COMMU05_07_H

/* The etc/commu05/07 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* The overlay's step table: the handlers the entry stub dispatches, selected
 * by the commu step byte commu00 owns. */
#define COMMU05_STEP_COUNT 3

/* The page counts of the three lists. */
typedef struct {
    u8 pages[3];
} Commu05State;

extern Commu05State D_801D19F0;
/* The page shown, counted across the three lists. */
extern s8           D_801D19F4;

void       func_801D1048(s16 x, s16 y, u8 group);
void       func_801D129C(s16 x, s16 y, u8 group);
void       func_801D14C8(s16 x, s16 y, s32 group);
void       func_801D1724(u16 x, u16 y);
extern u8  D_801457E8[][5];
extern u8  D_80145E60[];
extern u8  D_80145E61[];
extern u16 D_801D197C[][2];
extern u8  D_80145E30[];

/* The entry rows of the shared executable's fairy list (D_80145E48) and the
 * 5-byte icon cells each row byte selects (D_801457E8). */
extern u8   D_80145E48[];
extern char D_801D0C04[];

/* The background panel's cell origins, a u and a v byte per tile:
 * D_801D199C, D_801D19BC and D_801D19DC. */
extern u8 D_801D0C0C[];

/* g_EmiOverlayHeader */
/* D_801D1950 */
extern Callback g_Commu05Steps[COMMU05_STEP_COUNT];
extern u8       D_801D195C[];
extern u8       D_801D1964[];
extern u8       D_801D196C[];
extern u8       D_801D1974[];
extern u8       D_801D199C[][2];
extern u8       D_801D19BC[][2];
extern u8       D_801D19DC[][2];

#endif
