#ifndef OVERLAY_ETC_COMMU02_08_H
#define OVERLAY_ETC_COMMU02_08_H

/* The etc/commu02/08 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern OverlayHeader D_801D0C00;
/* The overlay's step and sub-step handler pools. The tables overlap: each entry
 * stub starts at its own offset into one callback run, so the counts stay open
 * until a data pass proves each reader's range. */
extern Callback      D_801DABCC[];
extern Callback      D_801DABD8[];
extern Callback      D_801DABE0[];
extern Callback      D_801DAC14[];
extern Callback      D_801DAC20[];
extern Callback      D_801DACB8[];
extern Callback      D_801DACC4[];
extern Callback      D_801DACD4[];
extern Callback      D_801DACF8[];
extern Callback      D_801DAD68[];
extern Callback      D_801DAD74[];
extern Callback      D_801DAD7C[];
extern Callback      D_801DADEC[];
extern Callback      D_801DAE00[];
extern Callback      D_801DAE24[];
extern Callback      D_801DAE30[];
extern Callback      D_801DAE44[];
extern Callback      D_801DAE68[];
extern Callback      D_801DAE74[];
extern u8            g_MenuPortraitAtlas[];

/* The overlay's state byte the guarded step advances. */
extern u8  D_801DB0B4;
extern s8  D_801DB0C4;
extern s16 D_801DB0C8;
extern s8  D_801DB0B8;
extern u8  D_801F2944;
extern u8  D_801F2945;
extern s32 D_801DB07C;
extern u8  D_801DAAA8;
extern u8  D_801DB0D0;
extern u8  D_801DB0D4;
extern u8  D_801DB0D8;
extern s8  D_801DB0DC;
extern u8 D_801DB0CC;

s32 func_801D7EA0(u8);

s32 func_801D92F4(u8);

s8 func_801DA114();

#endif
