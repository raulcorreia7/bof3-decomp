#include "battle_03.h"

/* Battle/03's retail .data, 0x801EABB8..0x801ED9D0, in address order.
 * The dispatch tables name their in-overlay targets; a target outside this
 * overlay (the exe and the boss overlay at 0x800C0000) stays an address
 * literal.  The runtime work areas are all zero in the retail image and stay
 * explicitly initialised so they keep their place in .data.  A span that no
 * declared type describes is one s_gap container; its interior D_ names stay
 * address-named views that the linker pins. */

/* In-overlay dispatch targets (split assembly units). */

/* 0x801EABB8 */
Callback D_801EABB8[5] = {
    (Callback)func_801D1C90, (Callback)func_801D1D10, (Callback)func_801D1E8C,
    (Callback)func_801D22AC, (Callback)func_801D24D4,
};

/* 0x801EABCC */
static u32 s_gap_801EABCC[3] = {
    0x40001000,
    0x20008000,
    0x00080004,
};

/* 0x801EABD8 */
Callback D_801EABD8[3] = {
    (Callback)func_801D22E8,
    (Callback)Battle_DrawEntrances,
    (Callback)func_801D2480,
};

/* 0x801EABE4 */
Callback D_801EABE4[8] = {
    (Callback)func_80096A74, (Callback)func_80096F00, (Callback)func_8009834C, (Callback)func_800980A8,
    (Callback)func_801D251C, (Callback)Battle_ArmCommands, (Callback)func_8009B274, (Callback)func_800A4688,
};

/* 0x801EAC04 */
Callback D_801EAC04[3] = {
    (Callback)func_801D277C,
    (Callback)func_801D28E8,
    (Callback)func_801D2A24,
};

/* 0x801EAC10 */
Callback D_801EAC10[5] = {
    (Callback)func_801D2B1C, (Callback)func_801D3014, (Callback)func_801D3C88,
    (Callback)func_801D3FEC, (Callback)func_801D43EC,
};

/* 0x801EAC24 */
Callback D_801EAC24[2] = {
    (Callback)func_801D2B58,
    (Callback)func_801D2FC0,
};

/* 0x801EAC2C */
Callback D_801EAC2C[6] = {
    (Callback)func_801D3050, (Callback)func_801D3168, (Callback)func_801D3050,
    (Callback)func_801D31C0, (Callback)func_801D32C8, (Callback)func_801D3A28,
};

/* 0x801EAC44 */
Callback D_801EAC44[2] = {
    (Callback)func_801D31FC,
    (Callback)func_801D3280,
};

/* 0x801EAC4C */
Callback D_801EAC4C[3] = {
    (Callback)Battle_SelectAbility,
    (Callback)func_801D3624,
    (Callback)func_801D39BC,
};

/* 0x801EAC58: the abilities `Recall` (ability 36 in GAME.EMI) casts at random.
 * Battle_PickTarget (0x801D3844) picks a slot with RANDOM_MASK(0x1F) and makes that
 * ability the action's ability. 32 slots, one ability ID each; the repeated
 * Burn entry weights the pick. */
/* D_801EAC58 */
volatile u8 g_BattleRecallAbilities[32] = {
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76,
    0x5B, 0x5B, 0x5E, 0x5E, 0x64, 0x61, 0x67, 0x5C, 0x5F, 0x65, 0x62, 0x46, 0x4B, 0x52, 0x54, 0x55,
};

/* 0x801EAC78: the abilities `MagicShuffle` (37) and `Trump` (140) cast at
 * random. Battle_PickTarget (0x801D3844) picks a slot with RANDOM_MASK(0x1F) and
 * makes that ability the action's ability. 32 slots, one ability ID each; the
 * repeated Burn entry weights the pick. */
/* D_801EAC78 */
volatile u8 g_BattleMagicShuffleAbilities[32] = {
    0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x5B, 0x5B, 0x5E, 0x5E, 0x64, 0x61, 0x67, 0x5C,
    0x5F, 0x65, 0x62, 0x66, 0x6A, 0x5D, 0x60, 0x46, 0x47, 0x4B, 0x52, 0x54, 0x55, 0x6B, 0x6C, 0x37,
};

/* 0x801EAC98 */
Callback D_801EAC98[3] = {
    (Callback)func_801D3A64,
    (Callback)func_801D3BB4,
    (Callback)func_801D3C1C,
};

/* 0x801EACA4 */
Callback D_801EACA4[3] = {
    (Callback)func_801D3CC4,
    (Callback)func_801D3E80,
    (Callback)Battle_FinishEffectLoad,
};

/* 0x801EACB0 */
Callback D_801EACB0[3] = {
    (Callback)func_801D4028,
    (Callback)func_801D409C,
    (Callback)func_801D42B4,
};

/* 0x801EACBC */
Callback D_801EACBC[3] = {
    (Callback)func_801D4AFC,
    (Callback)func_801D5024,
    (Callback)Battle_WaitVoiceSlots,
};

/* 0x801EACC8 */
Callback D_801EACC8[3] = {
    (Callback)func_801D4B38,
    (Callback)func_801D5008,
    (Callback)Battle_WaitVoiceSlots,
};

/* 0x801EACD4 */
Callback D_801EACD4[5] = {
    (Callback)func_801D67B0, (Callback)func_801D6C84, (Callback)func_801D6DE4,
    (Callback)func_801D6EEC, (Callback)func_801D71A4,
};

/* 0x801EACE8 */
Callback D_801EACE8[3] = {
    (Callback)func_801D67EC,
    (Callback)func_801D6818,
    (Callback)Battle_LoadEndOverlay,
};

/* 0x801EACF4 */
Callback D_801EACF4[3] = {
    (Callback)func_801D6CC0,
    (Callback)func_801D6D90,
    (Callback)func_801EEC58,
};

/* 0x801EAD00 */
Callback D_801EAD00[3] = {
    (Callback)func_801D6E20,
    (Callback)func_801D6EAC,
    (Callback)func_801EEC04,
};

/* 0x801EAD0C */
Callback D_801EAD0C[5] = {
    (Callback)func_801D67EC, (Callback)func_801D6818, (Callback)Battle_ReloadPartySprites,
    (Callback)Battle_ReloadAreaAudio, (Callback)Battle_WaitAreaReload,
};

/* 0x801EAD20 */
Callback D_801EAD20[4] = {
    (Callback)Battle_ReloadFieldText,
    (Callback)Battle_ReloadMusicBank,
    (Callback)Battle_WriteBackParty,
    (Callback)func_801D74D4,
};

/* 0x801EAD30 */
s16 D_801EAD30[144] = {
    2,  0, 103, 0, 0,  2, 105, 2, 1,  0, 104, 0, 3,  2, 102, 2, 2,  0, 74,  0, 0,   2, 76,  2, 1,   0, 75, 0, 3,   2,
    73, 2, 2,   0, 70, 0, 0,   2, 72, 2, 1,   0, 71, 0, 3,   2, 69, 2, 2,   0, 102, 0, 0,   2, 104, 2, 1,  0, 103, 0,
    3,  2, 101, 2, 2,  0, 278, 0, 0,  2, 280, 2, 1,  0, 279, 0, 3,  2, 277, 2, 2,   0, 38,  0, 0,   2, 40, 2, 1,   0,
    39, 0, 3,   2, 37, 2, 2,   0, 94, 0, 0,   2, 96, 2, 1,   0, 95, 0, 3,   2, 93,  2, 2,   0, 188, 0, 0,  2, 190, 2,
    1,  0, 189, 0, 3,  2, 187, 2, 2,  0, 282, 0, 0,  2, 284, 2, 1,  0, 283, 0, 3,   2, 281, 2,
};

/* 0x801EAE50 */
u16 D_801EAE50[34] = {
    0x0069, 0x000C, 0x0014, 0x0006, 0x0069, 0x000E, 0x0118, 0x000F, 0x0118, 0x00B4, 0x0028, 0x000F,
    0x0048, 0x000F, 0x0000, 0x0000, 0x004C, 0x0011, 0x0038, 0x0006, 0x0068, 0x000F, 0x0141, 0x00F1,
    0x0069, 0x0003, 0x0015, 0x0006, 0x0060, 0x0016, 0x00BE, 0x0016, 0x011C, 0x0016,
};

/* 0x801EAE94 */
/* D_801EAE94 */
u8 s_BattlePanelOffsets[14][2] = {
    {0x10, 0x10}, {0x10, 0x00}, {0x10, 0x20}, {0x00, 0x10}, {0x20, 0x10}, {0x00, 0x00}, {0x20, 0x00},
    {0x00, 0x00}, {0x15, 0x12}, {0xA0, 0x3A}, {0x5D, 0x00}, {0xBB, 0x00}, {0x19, 0x01}, {0x00, 0x00},
};

/* 0x801EAEB0 */
volatile u32 D_801EAEB0[14] = {
    0x006B7441, 0x00000000, 0x006C6241, 0x00000000, 0x00657355, 0x00000000, 0x00617845,
    0x00000000, 0x00666544, 0x00000000, 0x00676843, 0x00000000, 0x00637345, 0x00000000,
};

/* 0x801EAEE8 */
BattlePanelFrame D_801EAEE8[7] = {
    {108, 122, {0x97, 0x00, 0x76, 0x00}}, {140, 62, {0x9F, 0x00, 0x54, 0x00}},  {140, 142, {0x9F, 0x00, 0x8B, 0x00}},
    {88, 101, {0x85, 0x00, 0x6F, 0x00}},  {191, 101, {0xBA, 0x00, 0x6F, 0x00}}, {88, 70, {0x82, 0x00, 0x52, 0x00}},
    {191, 70, {0xBC, 0x00, 0x52, 0x00}},
};

/* 0x801EAF20 */
static u8 s_gap_801EAF20[12] = {
    0x0B, 0x03, 0x09, 0x00, 0x06, 0x01, 0x05, 0x00, 0x70, 0x41, 0x12, 0x00,
};

/* 0x801EAF2C */
volatile u8 D_801EAF2C[16] = {
    0x34, 0xF4, 0x04, 0x04, 0x37, 0xF4, 0xFC, 0x04, 0x34, 0xF7, 0x04, 0xFC, 0x37, 0xF7, 0xFC, 0xFC,
};

/* 0x801EAF3C */
/* D_801EAF3C */
volatile u16 g_BattleTurnPriorityMultipliers[6] = {
    0x0064, 0x007D, 0x0096, 0x00C8, 0x00FA, 0x0000,
};

/* 0x801EAF48 */
volatile s8 D_801EAF48[64] = {
    4, 2, 2, 2, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -2, -4, 6,  3, 3, 3, 0, 0, 0, 0, 0, 0, -2, -2, -2, -3, -3, -6,
    8, 4, 4, 4, 0, 0, 0, 0, 0, 0, -3, -3, -3, -4, -4, -8, 10, 5, 5, 5, 0, 0, 0, 0, 0, 0, -4, -4, -4, -5, -5, -10,
};

/* 0x801EAF88 */
/* D_801EAF88 */
volatile u8 g_BattleLevelThresholds[12] = {
    0x10, 0x24, 0x40, 0x63, 0x63, 0x63, 0x08, 0x10, 0x20, 0x30, 0x63, 0x63,
};

/* 0x801EAF94 */
/* D_801EAF94 */
u8 s_BattleDamageBandDivisors[12] = {
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x12, 0x14, 0x00, 0x00, 0x00,
};

/* 0x801EAFA0 */
s32 D_801EAFA0[8] = {
    218, 230, 243, 256, 269, 282, 294, 307,
};

/* 0x801EAFC0 */
s16 D_801EAFC0[8] = {
    300, 200, 200, 150, 125, 100, 50, 0,
};

/* 0x801EAFD0 */
u16 D_801EAFD0[18] = {
    0x0300, 0x0400, 0x0500, 0x0301, 0x0401, 0x0501, 0x0302, 0x0402, 0x0502,
    0x0303, 0x0403, 0x0503, 0x0304, 0x0404, 0x0504, 0x0305, 0x0405, 0x0505,
};

/* 0x801EAFF4 */
/* D_801EAFF4 */
u8 s_BattleStatusRecoveryPenalties[8] = {
    0xC8, 0x96, 0x64, 0x4B, 0x32, 0x19, 0x00, 0x00,
};

/* 0x801EAFFC */
/* D_801EAFFC */
u8 s_BattleStatusRecoveryChances[4] = {
    0x19,
    0x32,
    0x4B,
    0x00,
};

/* 0x801EB000 */
/* D_801EB000 */
u8 s_BattleActionNames[12][13] = {
    "Attack",
    T_SP T_NUM "\x1B" T_NUM "\x1C",
    "Examine",
    T_SP T_NUM "\x1F" T_NUM "\x20",
    "Defend",
    "Charge",
    "Reprisal",
    "Critical",
    "Lucky" T_SP "Strike",
    "Instant" T_SP "Kill",
    "Escape",
    "Counter",
};

/* 0x801EB09C */
volatile u16 D_801EB09C[1][10] = {
    {0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022},
};

/* 0x801EB0B0 */
/* D_801EB0B0 */
s8 g_BattlePanelOffsets[88] = {
    4,  -16, -4, -16, -4, -16, 4, -16, 0,  -16, 0, -16, 0,  -12, 0, -12, 0,  -25, 0, -25, 0,  -25,
    0,  -25, 0,  -16, 0,  -16, 4, -16, -4, -16, 0, -30, 0,  -30, 0, -30, 0,  -30, 4, -16, -4, -16,
    4,  -16, -4, -16, 4,  -6,  0, -6,  0,  -6,  0, -6,  -8, -20, 8, -20, -2, -12, 2, -12, 4,  -22,
    -4, -22, 0,  -22, 0,  -22, 4, -16, 0,  -16, 0, -16, 0,  -16, 0, -18, 0,  -18, 0, -18, 0,  -18,
};

/* 0x801EB108 */
/* D_801EB108 */
u8 s_BattlePanelYOffsets[20] = {
    0x18, 0x18, 0x20, 0x1C, 0x34, 0x34, 0x1C, 0x1C, 0x2E, 0x2E,
    0x26, 0x26, 0x14, 0x14, 0x28, 0x20, 0x28, 0x26, 0x00, 0x00,
};

/* 0x801EB11C */
static u8 s_gap_801EB11C[4] = {0};

/* 0x801EB120 */
Callback D_801EB120[15] = {
    (Callback)func_801DEF0C, (Callback)func_801DEFDC, (Callback)func_801DF3B8, (Callback)func_801DF3F8,
    (Callback)func_801DF8AC, (Callback)func_801DFA1C, (Callback)func_801DFBDC, (Callback)func_801E1670,
    (Callback)func_801E1990, (Callback)func_801E1B5C, (Callback)func_801E1B64, (Callback)func_801E1C78,
    (Callback)func_801E1CD8, (Callback)func_801DF768, (Callback)func_801DF7EC,
};

/* 0x801EB15C */
Callback D_801EB15C[11] = {
    (Callback)func_801DF914, (Callback)func_801DF914, (Callback)func_801DF914, (Callback)func_801DF914,
    (Callback)func_801DF914, (Callback)func_801DF914, (Callback)func_801DF914, (Callback)func_801DF914,
    (Callback)func_801DF914, (Callback)func_801DF914, (Callback)func_801DF914,
};

/* 0x801EB188 */
Callback D_801EB188[1] = {
    (Callback)func_801E1E7C,
};

/* 0x801EB18C */
/* D_801EB18C */
u8 s_BattleCharacterSprites[0x28] = {
    0x0D, 0x26, 0x19, 0x0A, 0x0A, 0x04, 0x23, 0x12, 0x0B, 0x0A, 0x20, 0x00, 0x21, 0x16,
    0x10, 0x13, 0x12, 0x16, 0x21, 0x12, 0x12, 0x21, 0x00, 0x08, 0x10, 0x13, 0x11, 0x0D,
    0x0D, 0x11, 0x11, 0x00, 0x00, 0x0F, 0x0F, 0x0C, 0x0C, 0x00, 0x00, 0x00,
};

/* 0x801EB1B4 */
/* D_801EB1B4 */
Callback g_BattleTaskFuncs[2] = {
    (Callback)func_801DFA60,
    (Callback)func_801DFB64,
};

/* 0x801EB1BC */
Callback D_801EB1BC[6] = {
    (Callback)func_801DFC20, (Callback)func_801DFC70, (Callback)func_801DFC20,
    (Callback)func_801E046C, (Callback)func_801E0744, (Callback)func_801E1450,
};

/* 0x801EB1D4 */
Callback D_801EB1D4[3] = {
    (Callback)func_801DFCB4,
    (Callback)func_801E019C,
    (Callback)func_801E020C,
};

/* 0x801EB1E0 */
Callback D_801EB1E0[5] = {
    (Callback)func_801E04B0, (Callback)func_801E0554, (Callback)func_801E05EC,
    (Callback)func_801E06EC, (Callback)func_801E020C,
};

/* 0x801EB1F4 */
Callback D_801EB1F4[7] = {
    (Callback)func_801E0788, (Callback)func_801E0F0C, (Callback)func_801E1050, (Callback)func_801E10C8,
    (Callback)func_801E1298, (Callback)func_801E10C8, (Callback)func_801E10C8,
};

/* 0x801EB210 */
Callback D_801EB210[2] = {
    (Callback)func_801E12DC,
    (Callback)func_801E13B8,
};

/* 0x801EB218 */
Callback D_801EB218[3] = {
    (Callback)func_801E1494,
    (Callback)func_801E019C,
    (Callback)func_801E15CC,
};

/* 0x801EB224 */
Callback D_801EB224[3] = {
    (Callback)func_801E16B4,
    (Callback)func_801E1888,
    (Callback)func_801E1938,
};

/* 0x801EB230 */
/* D_801EB230 */
u8 s_BattleCharacterStepIds[0x28] = {
    0x09, 0x19, 0x11, 0x0B, 0x18, 0x01, 0x30, 0x03, 0x25, 0x00, 0x21, 0x00, 0x21, 0x16,
    0x14, 0x1F, 0x03, 0x16, 0x21, 0x03, 0x03, 0x21, 0x00, 0x16, 0x14, 0x1F, 0x0D, 0x17,
    0x17, 0x11, 0x11, 0x00, 0x00, 0x30, 0x30, 0x12, 0x12, 0x00, 0x00, 0x00,
};

/* 0x801EB258 */
Callback D_801EB258[5] = {
    (Callback)func_801E19DC, (Callback)func_801E1A14, (Callback)func_801E1ADC,
    (Callback)func_801E1AE4, (Callback)func_801E1B04,
};

/* 0x801EB26C */
Callback D_801EB26C[2] = {
    (Callback)func_801E1BA8,
    (Callback)func_801E1C58,
};

/* 0x801EB274 */
Callback D_801EB274[2] = {
    (Callback)func_801E1D1C,
    (Callback)func_801E1D88,
};

/* 0x801EB27C */
Callback D_801EB27C[3] = {
    (Callback)func_801E1EC0,
    (Callback)func_801E2024,
    (Callback)func_801E2120,
};

/* 0x801EB288 */
static u8 s_gap_801EB288[12] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01, 0x00, 0x00,
};

/* 0x801EB294 */
Callback D_801EB294[1] = {
    (Callback)func_801E31C8,
};

/* 0x801EB298 */
Callback D_801EB298[63] = {
    (Callback)0x00000000u,   (Callback)func_800C1804, (Callback)func_800C1AA8, (Callback)func_800C1860,
    (Callback)func_800C1820, (Callback)func_800C190C, (Callback)func_800C1820, (Callback)func_800C1B40,
    (Callback)func_800C1804, (Callback)func_800C1CD8, (Callback)func_800C1DC4, (Callback)func_800C1EB0,
    (Callback)func_800C1804, (Callback)func_800C181C, (Callback)func_800C1A34, (Callback)func_800C1804,
    (Callback)func_800C1804, (Callback)func_800C1CC4, (Callback)func_800C1804, (Callback)func_800C19B4,
    (Callback)func_800C19BC, (Callback)func_800C184C, (Callback)func_800C19E8, (Callback)func_800C1B84,
    (Callback)func_800C181C, (Callback)func_800C19E4, (Callback)func_800C1CD8, (Callback)func_800C1804,
    (Callback)func_800C1804, (Callback)func_800C1804, (Callback)func_800C1850, (Callback)func_800C1B6C,
    (Callback)func_800C1D88, (Callback)func_800C1804, (Callback)func_800C1804, (Callback)func_800C1804,
    (Callback)func_800C18F0, (Callback)func_800C1804, (Callback)func_800C1804, (Callback)func_800C1804,
    (Callback)func_800C181C, (Callback)func_800C181C, (Callback)func_800C1950, (Callback)func_800C1810,
    (Callback)func_800C1804, (Callback)func_800C1804, (Callback)func_800C1C58, (Callback)func_800C1804,
    (Callback)func_800C1DB0, (Callback)func_800C1804, (Callback)func_800C1C98, (Callback)func_800C193C,
    (Callback)func_800C1804, (Callback)func_800C18F0, (Callback)func_800C1A54, (Callback)func_800C18F0,
    (Callback)func_800C18FC, (Callback)func_800C1810, (Callback)func_800C1814, (Callback)func_800C1810,
    (Callback)func_800C18FC, (Callback)func_800C1838, (Callback)func_800C1864,
};

/* 0x801EB394 */
/* D_801EB394 */
u8 s_BattlePartialPartyTargetWeights[3][2] = {
    {0x09, 0x07},
    {0x0C, 0x04},
    {0x08, 0x08},
};

/* 0x801EB39C */
/* D_801EB39C */
u8 s_BattleFullPartyTargetWeights[6][3] = {
    {0x06, 0x06, 0x04}, {0x0A, 0x03, 0x03}, {0x06, 0x05, 0x05},
    {0x08, 0x05, 0x03}, {0x06, 0x06, 0x04}, {0x08, 0x05, 0x03},
};

/* 0x801EB3B0 */
Callback D_801EB3B0[12] = {
    (Callback)func_801E320C, (Callback)func_801E32AC, (Callback)func_801E35D8, (Callback)func_801E3638,
    (Callback)func_801E3980, (Callback)func_801E3A00, (Callback)func_801E3B68, (Callback)func_801E4AE8,
    (Callback)func_801E4D8C, (Callback)func_801E4F64, (Callback)func_801E52E8, (Callback)func_801E5288,
};

/* 0x801EB3E0 */
static u8 s_gap_801EB3E0[4] = {0};

/* 0x801EB3E4 */
Callback D_801EB3E4[2] = {
    (Callback)func_801E32F0,
    (Callback)func_801E3438,
};

/* 0x801EB3EC */
Callback D_801EB3EC[2] = {
    (Callback)func_801E3334,
    (Callback)func_801E3398,
};

/* 0x801EB3F4 */
Callback D_801EB3F4[2] = {
    (Callback)func_801E347C,
    (Callback)func_801E352C,
};

/* 0x801EB3FC */
Callback D_801EB3FC[2] = {
    (Callback)func_801E383C,
    (Callback)func_801E38C0,
};

/* 0x801EB404 */
Callback D_801EB404[2] = {
    (Callback)func_801E3A44,
    (Callback)func_801E3B04,
};

/* 0x801EB40C */
Callback D_801EB40C[6] = {
    (Callback)func_801E3BAC, (Callback)func_801E3BD0, (Callback)func_801E3BAC,
    (Callback)func_801E4490, (Callback)func_801E4760, (Callback)func_801E4928,
};

/* 0x801EB424 */
Callback D_801EB424[3] = {
    (Callback)func_801E3C14,
    (Callback)func_801E4104,
    (Callback)func_801E414C,
};

/* 0x801EB430 */
Callback D_801EB430[5] = {
    (Callback)func_801E44D4, (Callback)func_801E4544, (Callback)func_801E45DC,
    (Callback)func_801E46EC, (Callback)func_801E414C,
};

/* 0x801EB444 */
Callback D_801EB444[4] = {
    (Callback)func_801E47A4,
    (Callback)func_801E47E0,
    (Callback)func_801E483C,
    (Callback)func_801E48D4,
};

/* 0x801EB454 */
Callback D_801EB454[3] = {
    (Callback)func_801E496C,
    (Callback)func_801E4104,
    (Callback)func_801E4A50,
};

/* 0x801EB460 */
Callback D_801EB460[3] = {
    (Callback)func_801E4B2C,
    (Callback)func_801E4C7C,
    (Callback)func_801E4D34,
};

/* 0x801EB46C */
Callback D_801EB46C[3] = {
    (Callback)func_801E4DD8,
    (Callback)func_801E4E10,
    (Callback)func_801E4ECC,
};

/* 0x801EB478 */
Callback D_801EB478[3] = {
    (Callback)func_801E4FA8,
    (Callback)func_801E50C0,
    (Callback)func_801E51DC,
};

/* 0x801EB484 */
static u8 s_gap_801EB484[16] = {
    0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* 0x801EB494 */
/* D_801EB494 */
u8 s_BattleBattlerStepIds[48] = {
    0xFF, 0xFF, 0xFF, 0x05, 0x04, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x07, 0x08, 0x08, 0x70, 0x41, 0x12, 0x00,
};

/* 0x801EB4C4 */
static u8 s_gap_801EB4C4[0x14] = {0};

/* 0x801EB4D8 */
BattleTurn* g_BattleActorTurn = 0;

/* 0x801EB4DC */
BattleEventSlot* D_801EB4DC = 0;

/* 0x801EB4E0 */
PartyMember* g_BattleEffectBattler = 0;

/* 0x801EB4E4 */
static u8 s_gap_801EB4E4[0x6C] = {0};

/* 0x801EB550 */
BattleRank D_801EB550[22] = {0};

/* 0x801EB5A8 */
u8 D_801EB5A8 = 0;

/* 0x801EB5AC */
static u8 s_gap_801EB5AC[8] = {0};

/* 0x801EB5B4 */
u8* D_801EB5B4[31] = {0};

/* 0x801EB630 */
EnemyBattler g_BattleEnemyBattlers[8] = {0};

/* 0x801EBEF0 */
static u8 s_gap_801EBEF0[0x14] = {0};

/* 0x801EBF04 */
u8 D_801EBF04 = 0;

/* 0x801EBF08 */
/* D_801EBF08 */
u8* g_BattleMessageSlot = 0;

/* 0x801EBF0C */
static u8 s_gap_801EBF0C[0x14] = {0};

/* 0x801EBF20 */
/* D_801EBF20 */
/* The party battler rows func_801E8684 copies into g_Game.members; func_801E7B34 and func_801D6818 read
 * their header.flags and turn.action_flags. */
PartyMember s_BattleBattlerTemplates[BATTLE_PARTY_CHARACTERS_COUNT] = {0};

/* 0x801EC2E0 */
static u8 s_gap_801EC2E0[0x50] = {0};

/* 0x801EC330 */
BattleEffect g_BattleEffects[48] = {0};

/* 0x801ED9B0 */
PanelOwner D_801ED9B0[8] = {0};
