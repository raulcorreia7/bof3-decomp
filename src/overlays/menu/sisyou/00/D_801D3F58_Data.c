#include "sisyou_00.h"

/* The overlay's data block, in retail address order. */

/* Panel sprite frames handed to UI_DrawSpriteRun. */
u8 D_801D3F58[MASTER_MENU_SPRITE_BANK_SIZE] = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x00, 0x01, 0x03, 0x02, 0x03, 0x03, 0x05, 0x04, 0x04, 0x00, 0x01,
    0x04, 0x02, 0x03, 0x04, 0x05, 0x04, 0x05, 0x00, 0x01, 0x05, 0x02, 0x03, 0x05, 0x05, 0x04, 0x06, 0x00, 0x01,
    0x06, 0x02, 0x03, 0x06, 0x05, 0x04, 0x07, 0x00, 0x01, 0x07, 0x02, 0x03, 0x07, 0x05, 0x04, 0x08, 0x00, 0x01,
    0x08, 0x02, 0x03, 0x08, 0x05, 0x04, 0x09, 0x00, 0x01, 0x09, 0x02, 0x05, 0x09, 0x03, 0x06, 0x09, 0x04, 0x06,
    0x09, 0x05, 0x07, 0x0A, 0x00, 0x08, 0x0B, 0x00, 0x09, 0x0B, 0x01, 0x0A, 0x0B, 0x02, 0x0A, 0x0B, 0x03, 0x0A,
    0x0B, 0x04, 0x0A, 0x0B, 0x05, 0x0B, 0x0B, 0x06, 0x0C, 0x0C, 0x00, 0x0D, 0x0C, 0x05, 0x0E, 0x0D, 0x00, 0x0D,
    0x0D, 0x05, 0x0E, 0x0E, 0x00, 0x0D, 0x0E, 0x05, 0x0E, 0x0F, 0x00, 0x12, 0x0F, 0x01, 0x10, 0x0F, 0x02, 0x10,
    0x0F, 0x03, 0x10, 0x0F, 0x04, 0x10, 0x0F, 0x05, 0x13, 0x10, 0x00, 0x31, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

u8 D_801D3FE8[MASTER_MENU_SPRITE_090_SIZE] = {
    0x00, 0x00, 0x0F, 0x00, 0x01, 0x10, 0x00, 0x02, 0x10, 0x00, 0x03, 0x10, 0x00, 0x04, 0x10,
    0x00, 0x05, 0x11, 0x01, 0x00, 0x09, 0x01, 0x01, 0x0A, 0x01, 0x02, 0x0A, 0x01, 0x03, 0x0A,
    0x01, 0x04, 0x0A, 0x01, 0x05, 0x0B, 0x01, 0x06, 0x0C, 0x00, 0x00, 0xFF, 0x00, 0x00,
};

u8 D_801D4014[MASTER_MENU_SPRITE_0BC_SIZE] = {
    0x02, 0x00, 0x0D, 0x02, 0x05, 0x0E, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

u8 D_801D4020[MASTER_MENU_SPRITE_0C8_SIZE] = {
    0x12, 0x00, 0x12, 0x12, 0x01, 0x10, 0x12, 0x02, 0x10, 0x12, 0x03, 0x10,
    0x12, 0x04, 0x10, 0x12, 0x05, 0x13, 0x13, 0x00, 0x31, 0x00, 0x00, 0xFF,
};

/* Panel stat labels. */
char D_801D4038[MASTER_MENU_LABEL_SIZE]      = "Pwr";
char D_801D403C[MASTER_MENU_LABEL_SIZE]      = "Def";
char D_801D4040[MASTER_MENU_LABEL_SIZE]      = "Int";
char D_801D4044[MASTER_MENU_LABEL_SIZE]      = "Agl";
char D_801D4048[MASTER_MENU_LABEL_LONG_SIZE] = "Pois";
char D_801D4050[MASTER_MENU_LABEL_LONG_SIZE] = "Conf";

/* Panel atlas records. */
// clang-format off
MenuPortraitSprite D_801D4058[MASTER_MENU_ATLAS_COUNT] = {
    {120, 0, 176, 2},
    {40, 48, 240, 2},
    {80, 0, 32, 2},
    {160, 0, 192, 2},
    {200, 0, 208, 2},
    {40, 0, 0, 2},
    {80, 48, 208, 1},
    {0, 0, 16, 2},
    {120, 48, 224, 1},
    {120, 0, 176, 2},
    {0, 48, 224, 2},
    {160, 48, 240, 1},
};
// clang-format on

/* Master skill grants: {level threshold, ability id}; {99, 0xFF} marks an empty slot. */
MasterSkill D_801D4088[MASTER_COUNT][MASTER_SKILL_COUNT] = {
    {{2, ABILITY_RISKY_BLOW},
     {5, ABILITY_FOCUS},
     {8, ABILITY_SUPER_COMBO},
     {10, ABILITY_DISEMBOWEL},
     {99, 0xFF},
     {99, 0xFF}},
    {{1, 196}, {4, ABILITY_MEDITATION}, {6, ABILITY_MAGIC_BALL}, {8, 203}, {99, 0xFF}, {99, 0xFF}},
    {{2, ABILITY_SANCTUARY}, {5, ABILITY_RECALL}, {8, 185}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{2, ABILITY_MONOPOLIZE}, {3, ABILITY_INTIMIDATE}, {4, ABILITY_STEAL}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{2, ABILITY_CHARGE}, {4, ABILITY_COUNTER}, {6, ABILITY_RESIST}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{1, ABILITY_UNMOTIVATE}, {2, ABILITY_FEIGN_SWING}, {3, ABILITY_BACKHAND}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{2, ABILITY_TRUMP}, {5, ABILITY_BERSERK}, {8, ABILITY_SUDDENDEATH}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{2, 179}, {5, 207}, {8, ABILITY_BENEDICTION}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{2, 188}, {4, ABILITY_MIND_SWORD}, {6, ABILITY_ENLIGHTEN}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{2, 195}, {5, 198}, {8, 201}, {11, 206}, {15, ABILITY_CELERITY}, {99, 0xFF}},
    {{2, ABILITY_MIGHTY_CHOP}, {4, ABILITY_DEMONBANE}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{5, ABILITY_RISKY_BLOW}, {8, ABILITY_FOCUS}, {12, ABILITY_SUPER_COMBO}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{5, ABILITY_RISKY_BLOW}, {8, ABILITY_FOCUS}, {12, ABILITY_SUPER_COMBO}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{5, ABILITY_RISKY_BLOW}, {8, ABILITY_FOCUS}, {12, ABILITY_SUPER_COMBO}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{5, ABILITY_RISKY_BLOW}, {8, ABILITY_FOCUS}, {12, ABILITY_SUPER_COMBO}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
    {{3, ABILITY_MIND_S_EYE},
     {5, ABILITY_HOLY_STRIKE},
     {7, ABILITY_WARDOFLIGHT},
     {9, ABILITY_AURA},
     {99, 0xFF},
     {99, 0xFF}},
    {{2, ABILITY_CHARM}, {5, ABILITY_SHADOWWALK}, {8, ABILITY_WAR_SHOUT}, {99, 0xFF}, {99, 0xFF}, {99, 0xFF}},
};

/* Master stat bonuses: hp, ap, power, defense, agility, intellect. */
// clang-format off
SisyouMasterStats D_801D4154[MASTER_COUNT] = {
    {2, -2, 2, 1, 0, -3},
    {0, 1, -1, -1, 0, 2},
    {-1, 1, -2, 1, 0, 2},
    {-1, -2, 1, 0, 1, 0},
    {4, 0, 1, 3, -3, -3},
    {0, 0, 0, 0, 0, 0},
    {4, 3, -1, -1, -1, -1},
    {0, 1, -2, 0, 0, 1},
    {0, 4, -2, -2, 0, 4},
    {-3, 3, 1, -3, 1, 3},
    {2, -2, 2, 1, -1, -1},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0},
    {-6, -6, 2, 2, 1, 2},
    {-1, 0, -1, -1, 2, 0},
};
// clang-format on

u8 D_801D41BA = 0x00;
u8 D_801D41BB = 0x00;

/* Message ids the panels queue. */
u16 D_801D41BC[MASTER_MENU_MESSAGE_ID_COUNT] = {
    64, 0, 32, 128, 128, 0, 0, 144, 0, 43, 96, 92, 112, 132, 152, 80, 3, 0,
};

/* Step and sub-step handlers. */
Callback g_MasterMenuFuncs[MASTER_MENU_STEP_COUNT] = {
    func_801D2614, func_801D2688, func_801D278C, func_801D2BE8, func_801D32D4, func_801D3924, Master_ApplyMaster,
};

Callback g_MasterMenuSubFuncs[MASTER_MENU_SUBSTEP_COUNT] = {
    func_801D26C4,
    func_801D2738,
};

Callback D_801D4204[SISYOU_SUB2_HANDLER_COUNT] = {
    func_801D27C8, func_801D282C, func_801D28B0, func_801D29C8, func_801D2A4C, func_801D2B64,
};

Callback D_801D421C[SISYOU_SUB3_HANDLER_COUNT] = {
    func_801D0C48, func_801D0C88, func_801D2C24, func_801D2C64, func_801D12FC,
    func_801D2CA4, func_801D30C4, func_801D3148, func_801D3258,
};

Callback D_801D4240[SISYOU_SUB4_HANDLER_COUNT] = {
    func_801D0C48, func_801D0C88, func_801D3310, func_801D3350, func_801D12FC,
    func_801D3390, func_801D3714, func_801D3798, func_801D38A8,
};

Callback D_801D4264[SISYOU_SUB5_HANDLER_COUNT] = {
    func_801D3960,
    func_801D3A24,
    func_801D3E70,
};

u8 D_801D4270[MASTER_MENU_VALUE_COUNT] = {
    255, 255, 255, 3, 255, 3, 255, 255, 255, 6, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0,
};

/* Shop panel state. */
u8 g_MasterBannerLock = 0;
u8 g_MasterStep       = 0;
u8 g_MasterSubStep    = 0;
u8 g_MasterPanelLock  = 0;
