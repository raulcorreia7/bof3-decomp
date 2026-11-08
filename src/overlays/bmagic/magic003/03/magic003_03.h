#ifndef OVERLAY_BMAGIC_MAGIC003_03_H
#define OVERLAY_BMAGIC_MAGIC003_03_H

/* The bmagic/magic003/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8 D_801463D6;

typedef struct Magic003Steps801EEC04 {
    Callback steps[5];
} Magic003Steps801EEC04;

typedef struct Magic003Steps801EEC18 {
    Callback steps[4];
} Magic003Steps801EEC18;

extern Magic003Steps801EEC04 D_801EEC04;

void func_801EF324(void);

void func_801EF708(void);

extern Magic003Steps801EEC18 D_801EEC18;
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern u8                    D_801F0A84[];
extern BattleEffect          D_801F0B38[];
#define BMAGIC_EFFECT_SLOTS D_801F0B38
#define BMAGIC_EFFECT_COUNT 32

void func_801F0164(s32 arg0);

void func_801F0078(void);
void func_801F0550(s32 arg0);
void func_801F07B0(s32 arg0);

#endif
