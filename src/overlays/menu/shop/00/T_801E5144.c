#include "shop_00.h"

Callback g_MenuScreenSteps[MENU_SCREEN_COUNT] = {
    Menu_SelectScreen, func_801D1000, func_801D10E4, Menu_RunInn, func_801D1000, Menu_RunInoculation, Menu_RunPartySwap, Menu_RunSkillInk, func_801D3310, func_801E200C, func_801D6184,
};

Callback g_ShopStep2Steps[SHOP_STEP2_COUNT] = {
    func_801D1120, func_801D12C0, func_801D14B0, func_801D27EC, func_801D32C0,
};

Callback g_ShopStep2Sub0Steps[SHOP_STEP2_SUB0_COUNT] = {
    func_801D115C,
    func_801D1254,
};

Callback g_ShopStep2Sub1Steps[SHOP_STEP2_SUB1_COUNT] = {
    func_801D12FC,
};

Callback g_ShopStep2Sub2Steps[SHOP_STEP2_SUB2_COUNT] = {
    func_801D14EC, func_801D163C, func_801D1A90, func_801D1D60, func_801D1F74, func_801D20D0, func_801D23E4, func_801D26A8,
};

Callback g_ShopStep2Sub3Steps[SHOP_STEP2_SUB3_COUNT] = {
    func_801D2828, func_801D28D0, func_801D2D64, func_801D3014, func_801D3280,
};

Callback g_ShopStep8Steps[SHOP_STEP8_COUNT] = {
    func_801D334C,
    func_801D349C,
    func_801D34F0,
    func_801D352C,
};
