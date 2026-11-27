#ifndef OVERLAY_ETC_COMMU03_06_H
#define OVERLAY_ETC_COMMU03_06_H

/* The etc/commu03/06 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* g_EmiOverlayHeader */
/* Entries of the handler tables. */
#define COMMU03_STEP_COUNT  3
#define COMMU03_STEP0_COUNT 2
#define COMMU03_STEP1_COUNT 2
#define COMMU03_STEP2_COUNT 4
/* Message-table byte offsets, indexed by the fairy's cue id (D_801D1940). */
extern u16 D_800104E2[];
/* g_FairyRooms + 3: the selected room's cue count. */
extern u8  D_801457AB[];

/* D_801D18C8 */
extern Callback g_Commu03Steps[COMMU03_STEP_COUNT];
/* D_801D18D4 */
extern Callback g_Commu03Step0Steps[COMMU03_STEP0_COUNT];
/* D_801D18DC */
extern Callback g_Commu03Step1Steps[COMMU03_STEP1_COUNT];
/* D_801D18E4 */
extern Callback g_Commu03Step2Steps[COMMU03_STEP2_COUNT];
extern u8       D_801D18F4[];
extern u8       D_801D18F8[];
extern u8       D_801D18FC[];
extern u8*      D_801D1904;
extern u8*      D_801D1908;
extern u8*      D_801D190C;
extern u8       D_801D1918[];
extern s16      D_801D1940;
extern u8       D_801D1944;
extern u8       D_801D1948;

/* The overlay's state byte the guarded step advances. */

void func_801D1250(s16 x, s16 y);
void func_801D1714(s16 x, s16 y, u32 clut, u8* text);

#endif
