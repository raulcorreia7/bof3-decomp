#include "battle_03.h"

/* Overlay head .data, 0x801D0CB8..0x801D0F0C: the drop chances and the
 * queued-slot dispatch tables (mode, type and sub-type handlers). */

/* In-overlay dispatch targets (split assembly units). */

DropChances g_BattleDropChances = {
    0x00, 0x00, 0x01, 0x03, 0x07, 0x1F, 0x7F, 0xFF,
};

/* 0x801D0CC0: the queued slot's mode (+0x06, stored by Battle_AllocEffect)
 * selects one of these four effect handlers; Battle_UpdateEffects copies the
 * table and dispatches for every active slot. */
/* D_801D0CC0 */
BattleEffectModes g_BattleEffectModes = {
    (Callback)Battle_RunBattlerEffect,
    (Callback)Battle_RunMagicEffect,
    (Callback)func_800ADFBC,
    (Callback)Battle_RunBossEffect,
};

/* 0x801D0CD0: mode 0 handler (Battle_RunBattlerEffect) dispatches the queued
 * slot's effect_type (+0x05) here; 19 handlers, indices 0..0x12. */
/* D_801D0CD0 */
BattleBattlerEffectSteps g_BattleBattlerEffectSteps = {
    (Callback)func_801E5AEC,
    (Callback)Battle_UpdateDamageNumber,
    (Callback)Battle_UpdateScreenFlash,
    (Callback)Battle_UpdatePoseActor,
    (Callback)Battle_UpdateScreenFade,
    (Callback)func_801E6AA0,
    (Callback)Battle_UpdateAilmentActor,
    (Callback)Battle_UpdateBattlerGhost,
    (Callback)func_800C2FF4,
    (Callback)func_800AD26C,
    (Callback)func_800AD69C,
    (Callback)func_801E74B8,
    (Callback)Battle_UpdateFormChange,
    (Callback)func_800AD9CC,
    (Callback)func_800ADCC4,
    (Callback)func_800A8540,
    (Callback)func_800A8C60,
    (Callback)Battle_UpdateFormRestore,
    (Callback)func_800A8D80,
};

/* 0x801D0D1C: mode 1 handler (Battle_RunMagicEffect) dispatches the queued
 * slot's effect_type (+0x05) here; 110 handlers; BMagicEffectType names the used indices. */
/* D_801D0D1C */
BattleMagicEffectSteps g_BattleMagicEffectSteps = {
    (Callback)func_801E5AEC, (Callback)func_801EF2CC,       (Callback)func_800AE788, (Callback)func_801EF75C, (Callback)func_801EEF08, (Callback)func_801EF56C, (Callback)func_801EEE00,
    (Callback)func_801EF774, (Callback)func_801EF210,       (Callback)func_801EEFDC, (Callback)func_801EEE58, (Callback)func_801EF09C, (Callback)func_801EF16C, (Callback)func_801EEEE4,
    (Callback)func_801EEF84, (Callback)func_801EF010,       (Callback)func_801EF3F8, (Callback)func_801EEEBC, (Callback)func_801EFF44, (Callback)func_801EF2D0, (Callback)func_801EEF84,
    (Callback)func_801EEE4C, (Callback)func_801EEF74,       (Callback)func_801F0018, (Callback)func_801EEDF0, (Callback)func_801EEDA0, (Callback)func_801EED7C, (Callback)func_801EF310,
    (Callback)func_801EF73C, (Callback)func_801EF278,       (Callback)func_801EEE70, (Callback)func_801F0250, (Callback)func_801EF4E0, (Callback)func_801EF014, (Callback)func_801EF108,
    (Callback)func_801EF9E4, (Callback)func_801EEF9C,       (Callback)func_801EEFF4, (Callback)func_801EEFB0, (Callback)func_801EF0A8, (Callback)func_801EF000, (Callback)func_801EEFD0,
    (Callback)func_801EF0DC, (Callback)func_801EED98,       (Callback)func_801EF158, (Callback)func_801EEEC8, (Callback)func_801EF398, (Callback)func_801EEF6C, (Callback)func_801EF054,
    (Callback)func_801EEEA4, (Callback)func_801EEF70,       (Callback)func_801EEF78, (Callback)func_801EEF74, (Callback)func_801EED70, (Callback)func_801EEE9C, (Callback)func_801EEFF8,
    (Callback)func_801EEE5C, (Callback)func_801EEE90,       (Callback)func_801EF78C, (Callback)func_801EEF64, (Callback)func_801EEF48, (Callback)func_801EF190, (Callback)func_801EEDA4,
    (Callback)func_801EEF30, (Callback)func_801EF1E0,       (Callback)func_801EF02C, (Callback)func_801EF014, (Callback)func_800AE34C, (Callback)func_801EF9F0, (Callback)func_801EF20C,
    (Callback)func_801EF8CC, (Callback)func_801EF2D8,       (Callback)func_800AE4D0, (Callback)func_801EEFD8, (Callback)func_801EF4C4, (Callback)func_801EEFD4, (Callback)func_801EEEA0,
    (Callback)func_801EF080, (Callback)func_801EEED0,       (Callback)func_801EFAB8, (Callback)func_801EEE94, (Callback)func_801EEE38, (Callback)func_801EF0C0, (Callback)func_801EEE04,
    (Callback)func_801EEF3C, (Callback)func_801EF1B0,       (Callback)func_801EEF60, (Callback)func_801EEFF8, (Callback)func_801EEDE4, (Callback)func_801EF0D0, (Callback)func_801EEE68,
    (Callback)func_801EF268, (Callback)func_801EEEC0,       (Callback)func_800C1D30, (Callback)func_801EF064, (Callback)func_801EF004, (Callback)func_801EEEE0, (Callback)func_801EEF78,
    (Callback)func_801EF330, (Callback)Effect_StartPlaying, (Callback)func_801EF114, (Callback)func_801EF2D8, (Callback)func_801EEED4, (Callback)func_801EEE18, (Callback)func_801EEF30,
    (Callback)func_801EF668, (Callback)func_801EEF80,       (Callback)func_801EEFC0, (Callback)func_801EEE2C, (Callback)func_801EF04C,
};

/* 0x801D0ED4: mode 3 handler (Battle_RunBossEffect) dispatches the queued
 * slot's effect_type (+0x05) here; eight handlers. */
/* D_801D0ED4 */
BattleBossEffectSteps g_BattleBossEffectSteps = {
    (Callback)func_801E5AEC, (Callback)func_801EEE64, (Callback)func_800C1BEC, (Callback)func_800C1EA0,
    (Callback)func_800C1D54, (Callback)func_800C26D4, (Callback)func_800C1E2C, (Callback)func_800C1AA8,
};

/* 0x801D0EF4 */
BattleDamageNumberSteps g_BattleDamageNumberSteps = {
    (Callback)Battle_StartDamageNumber, (Callback)Battle_HoldDamageNumber, (Callback)Battle_RiseDamageNumber, (Callback)Battle_BounceDamageNumber, (Callback)Battle_EndDamageNumber,
};

static u8 s_gap_801D0F08[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
