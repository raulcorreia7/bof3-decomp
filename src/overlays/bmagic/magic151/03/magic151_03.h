#ifndef OVERLAY_BMAGIC_MAGIC151_03_H
#define OVERLAY_BMAGIC_MAGIC151_03_H

/* The bmagic/magic151/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8          D_800B4C90[];
extern u8          D_80149298[];
extern PartyMember s_BattleBattlerTemplates[BATTLE_PARTY_CHARACTERS_COUNT];

#define MAGIC151_STEP_COUNT 5

typedef struct Magic151Steps {
    Callback steps[MAGIC151_STEP_COUNT];
} Magic151Steps;

/* The battle panel rows the setup fills, one 0x24-byte row a panel. */
typedef struct BattlePanelRow {
    u8  mode_00;
    u8  unk_01;
    s16 x_02;
    s16 y_04;
    u8  unk_06;
    u8  unk_07;
    u8  battler;
    u8  pad_09[0x1B];
} BattlePanelRow;

ASSERT_SIZE(BattlePanelRow, 0x24);

/* The palette row the battle load copies. */
extern u8             D_801463B9;
extern BattlePanelRow D_80148332[];
/* The panel x offsets by scroll direction. */
extern s8             D_801EAEA4[];
/* The panel x and y offsets of each battler facing, two bytes a facing. */
extern s8             D_801EB0B0[];
extern s8             D_801EB0B1[];
/* The effect cells of each member row, indexed with the member stride. */
extern u8             D_801EBF47[];
extern u8             D_801EC039[];
extern u32            D_801EC044[];
/* The staged encounter origin and ground height. */
extern s32            D_801EC364;
extern s32            D_801EC368;
extern s32            D_801EC36C;
extern Magic151Steps  D_801EEC10;
extern Magic151Steps  D_801EEC24;

extern BMagicEffectSteps D_801EEC38;
void                     func_800A68A4(void);
void                     func_801DE190(u8 slot);
void                     func_801DE1B0(u8 slot);
void                     func_801F026C(void);
void                     func_801F0648(void);
void                     func_801F0D0C(u8 angle0, u8 angle1);
void                     func_801F14D0(s32 band_height, s16 radius, u16 jitter_mask);

extern Callback D_801F24B8[];
/* The draw step's handler table and its two-byte row per effect slot. */
extern u8       D_801F24D0[][2];
extern Callback D_801F24F0[];
extern Callback D_801F24FC[];
extern Callback D_801F250C[];
void            func_801F1DC0(void);
void            BMagic_DrawGlowRingInner(void);
void            BMagic_DrawGlowRingOuter(void);

#endif
