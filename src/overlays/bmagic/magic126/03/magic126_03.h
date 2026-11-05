#ifndef OVERLAY_BMAGIC_MAGIC126_03_H
#define OVERLAY_BMAGIC_MAGIC126_03_H

/* The bmagic/magic126/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The amount Effect_CountDownTimer adds to the effect work byte 9. */
#define EFFECT_TIMER_STEP 1

extern PartyBattler* D_801F22BC;

extern Callback D_801F1278[];
void            func_800AF764(void);
void            func_801EFD5C(void);

extern Callback D_801F1288[];
void            func_801F06AC(void);

extern Callback D_801F12AC[];
extern Callback D_801F1268[];
extern u8       D_801F12BC[];
void            func_801F11AC(void);
void            func_801F0ED0(void);

#endif
