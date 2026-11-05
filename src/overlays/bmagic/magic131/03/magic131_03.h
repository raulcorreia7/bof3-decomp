#ifndef OVERLAY_BMAGIC_MAGIC131_03_H
#define OVERLAY_BMAGIC_MAGIC131_03_H

/* The bmagic/magic131/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define EFFECT_ADVANCE_AT_COUNT(increment, limit)     \
    g_SpadWork->word_08.byte.unk_09 += (increment);   \
    if (g_SpadWork->word_08.byte.unk_09 == (limit)) { \
        g_SpadWork->unk_02 += 1;                      \
    }

extern PartyBattler* D_801F24E0;

extern Callback D_801F1BF4[];
void            func_801F030C(void);

extern Callback D_801F1C24[];
void            func_801F0D44(void);
void            func_801F0DF4(void);

extern Callback D_801F1C08[];
extern Callback D_801F1C48[];
void            func_801F06B4(void);

void func_801F1844(void);

#endif
