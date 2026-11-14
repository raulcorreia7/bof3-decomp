#ifndef OVERLAY_BMAGIC_MAGIC126_03_H
#define OVERLAY_BMAGIC_MAGIC126_03_H

/* The bmagic/magic126/03 overlay. Only this image includes the file. */

#define BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];
extern s16     D_1F800004;

extern Callback D_801F1268[];

extern Callback D_801F1278[];

extern Callback D_801F1288[];

extern BMagicRingShade D_801F1298[];

extern Callback D_801F12AC[];

/* One of the 128 records BMagic_AllocEffect claims: a task header, the spawn index and the battler it acts on;
 * func_801EEC04 runs each claimed record through func_801F091C as D_801F22BC with that battler swapped in. */
typedef struct Magic126Mote {
    TaskHeader   header; /* 0x00 */
    u8           unk_03;
    u8           unk_04; /* +0x04 spawn index; the angle is its low four bits */
    u8           unk_05;
    u8           pad_06[0x16];
    PartyMember* battler; /* +0x1C */
} Magic126Mote;

ASSERT_SIZE(Magic126Mote, 0x20);
ASSERT_OFFSET(Magic126Mote, unk_04, 0x04);
ASSERT_OFFSET(Magic126Mote, battler, 0x1C);

#define BMAGIC_EFFECT_SLOTS D_801F12BC
#define BMAGIC_EFFECT_COUNT 128

extern Magic126Mote D_801F12BC[];
void                func_801EFD5C(void);
void                func_801F06AC(void);
void                func_801F091C(void);

void                func_801F0ED0(void);
void                func_801F116C(void);
void                func_801F11AC(void);
extern PartyMember* D_801F22BC;

void BMagic_DrawGlowRingInner(void);

void func_801EF1C8(void);
void BMagic_DrawGlowRingOuter(void);

#endif
