#include "battle_15.h"

BattleEffectSteps D_80096994 = {func_800AD2EC, func_800AD434, func_800AD67C};
BattleEffectSteps D_800969A0 = {func_800AD71C, func_800AD808, func_800AD9AC};
BattleEffectSteps D_800969AC = {func_800ADA4C, func_800ADB74, func_800ADCA4};
BattleEffectSteps D_800969B8 = {func_800ADD44, func_800ADE6C, func_800ADF9C};
static u8 s_gap_800969C4[32] = {
    0x74, 0xE5, 0x0A, 0x80, 0x40, 0xE6, 0x0A, 0x80, 0xC8, 0xE6, 0x0A, 0x80, 0x28, 0xE7, 0x0A, 0x80,
    0x2C, 0xE8, 0x0A, 0x80, 0x40, 0xE6, 0x0A, 0x80, 0xC8, 0xE6, 0x0A, 0x80, 0x28, 0xE7, 0x0A, 0x80,
};
BattleMenuPanelModes D_800969E4 = {func_800B01F0, func_800B09CC, func_800B0CE4, func_800B138C, func_800B155C};
BattleMenuPanel0States D_800969F8 = {func_800B0250, func_800B0398, func_800B0410};
volatile u8 D_80096A04[4] = {0x25, 0x32, 0x64, 0x00};
BattleMenuPanel1States D_80096A08 = {func_800B0A2C, func_800B0A54, func_800B0AB0};
BattleMenuPanel2States D_80096A14 = {func_800B0D54, func_800B0E24, func_800B0E6C, func_800B0EC4, func_800B0F30};
static u8 s_gap_80096A28[12] = {
    0x25, 0x64, 0x00, 0x00, 0x41, 0x50, 0x25, 0x32, 0x64, 0x00, 0x00, 0x00,
};
BattleMenuPanel3States D_80096A34 = {func_800B13EC, func_800B14BC, func_800B1504};
BattleMenuPanel4States D_80096A40 = {func_800B15BC, func_800B1664, func_800B16D0};
static u8 s_gap_80096A4C[16] = {
    0x25, 0x33, 0x64, 0x2F, 0x25, 0x33, 0x64, 0x00, 0x25, 0x33, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
};
