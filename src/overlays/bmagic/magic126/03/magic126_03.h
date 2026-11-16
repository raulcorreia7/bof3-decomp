#ifndef OVERLAY_BMAGIC_MAGIC126_03_H
#define OVERLAY_BMAGIC_MAGIC126_03_H

/* The bmagic/magic126/03 overlay. Only this image includes the file. */

#define FAKE_DECL_BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"

extern s16 D_1F800004;
extern s16 g_ScratchPadHalves;

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
    u8           unk_06;
    u8           pad_07[5];
    u16          unk_0C;
    u16          unk_0E;
    s32          unk_10;
    s32          unk_14;
    u8           pad_18[4];
    PartyMember* battler; /* +0x1C */
} Magic126Mote;

ASSERT_SIZE(Magic126Mote, 0x20);
ASSERT_OFFSET(Magic126Mote, unk_04, 0x04);
ASSERT_OFFSET(Magic126Mote, unk_0C, 0x0C);
ASSERT_OFFSET(Magic126Mote, unk_0E, 0x0E);
ASSERT_OFFSET(Magic126Mote, unk_10, 0x10);
ASSERT_OFFSET(Magic126Mote, unk_14, 0x14);
ASSERT_OFFSET(Magic126Mote, battler, 0x1C);

#define BMAGIC_EFFECT_SLOTS D_801F12BC
#define BMAGIC_EFFECT_COUNT 128

extern Magic126Mote D_801F12BC[];
void                func_801EFD5C(void);
void                func_801F06AC(void);
void                func_801F091C(void);

void                BMagic_DrawMote(void);
void                func_801F116C(void);
void                func_801F11AC(void);
extern PartyMember* D_801F22BC;
/* The current record as a mote: D_801F22BC points into D_801F12BC. */
#define MAGIC126_MOTE ((Magic126Mote*)D_801F22BC)

void BMagic_DrawGlowRingInner(void);

void func_801EF1C8(void);
void BMagic_DrawGlowRingOuter(void);

#endif
