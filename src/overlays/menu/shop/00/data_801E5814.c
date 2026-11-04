#include "shop_00.h"

u8 D_801E5814[8] = "Pois" T_END;

u8 D_801E581C[8] = "Conf" T_END;

u8 g_MenuLabelPower[4] = "Pwr" T_END;

u8 g_MenuLabelDefense[4] = "Def" T_END;

u8 g_MenuLabelIntellect[4] = "Int" T_END;

u8 g_MenuLabelAgility[4] = "Agl" T_END;

u8 D_801E5834[8] = {0x08, 0x0A, 0x09, 0x0B, 0x0C, 0x0C, 0x00, 0x00};

u8 D_801E583C[8] = "EQUIP" T_END;

u8 D_801E5844[4] = "EXP" T_END;

u8 D_801E5848[8] = "NEXT" T_END;

u8 g_MenuPortraitAtlas[48] = {
    0x78, 0x00, 0xB0, 0x02, 0x28, 0x30, 0xF0, 0x02, 0x50, 0x00, 0x20, 0x02,
    0xA0, 0x00, 0xC0, 0x02, 0xC8, 0x00, 0xD0, 0x02, 0x28, 0x00, 0x00, 0x02,
    0x50, 0x30, 0xD0, 0x01, 0x00, 0x00, 0x10, 0x02, 0x78, 0x30, 0xE0, 0x01,
    0x78, 0x00, 0xB0, 0x02, 0x00, 0x30, 0xE0, 0x02, 0xA0, 0x30, 0xF0, 0x01,
};

u8 D_801E5880[24] = "Pwr" T_END T_END T_END "Def" T_END T_END T_END "Int" T_END T_END T_END "Agl";

u32 D_801E5898 = 0;

s32 D_801E589C[5] = {-12, -4, 12, 4, 12};

u8 MENU_CAPTION_ICON[4] = "`" T_END;

u8 MENU_CLOCK_COLON[4] = ">" T_END;

u8 D_801E58B8[4] = "Use" T_END;

u8 D_801E58BC[8] = "Sort" T_END;

u8 D_801E58C4[8] = "Drop" T_END;

u8 D_801E58CC[8] = "Eqip" T_END;

u8 D_801E58D4[8] = "Opti" T_END;

u8 D_801E58DC[8] = "Abil" T_END;

u8 D_801E58E4[4] = "Buy" T_END;

u8 D_801E58E8[8] = "Sell" T_END;

u8 D_801E58F0[8] = "Chng" T_END;

u8 D_801E58F8[8] = "Read" T_END;

u8 D_801E5900[8] = "Vtal" T_END;

u8 D_801E5908[8] = "Quit" T_END;

u8 D_801E5910[8] = "Form" T_END;

u8 D_801E5918[8] = "Bttn" T_END;

u8 D_801E5920[8] = "Init" T_END;

u8 D_801E5928[8] = "Note" T_END;

u8 D_801E5930[8] = "Fast" T_END;

u8 D_801E5938[8] = "Pool" T_END;

u8 D_801E5940[8] = "Ally" T_END;

u8 D_801E5948[8] = "Gene" T_END;

u8 D_801E5950[8] = "Knd" T_END;

u8 D_801E5958[8] = "Look" T_END;

u8 D_801E5960[4] = "End" T_END;

u8* g_MenuCommandLabels[23] = {
    D_801E58B8, D_801E58BC, D_801E58C4, D_801E58CC, D_801E58D4,
    D_801E58DC, D_801E58E4, D_801E58E8, D_801E58F0, D_801E58F8,
    D_801E5900, D_801E5908, D_801E5910, D_801E5918, D_801E5920,
    D_801E5928, D_801E5930, D_801E5938, D_801E5940, D_801E5948,
    D_801E5950, D_801E5958, D_801E5960,
};

u8 g_MenuCommandRows[][5] = {
    {0x04, 0x00, 0x01, 0x02, 0x0A},
    {0x04, 0x03, 0x04, 0x10, 0x11},
    {0x04, 0x05, 0x01, 0x0F, 0x13},
    {0x02, 0x06, 0x07, 0x00, 0x00},
    {0x02, 0x15, 0x08, 0x00, 0x00},
    {0x03, 0x09, 0x01, 0x02, 0x00},
    {0x02, 0x0B, 0x0E, 0x00, 0x00},
    {0x02, 0x0C, 0x12, 0x00, 0x00},
    {0x02, 0x14, 0x16, 0x00, 0x00},
};

u8 D_801E59F0[24] = "Pwr" T_END T_END T_END "Def" T_END T_END T_END "Int" T_END T_END T_END "Agl";

u8 D_801E5A08[8] = {0x08, 0x0A, 0x09, 0x0B, 0x0C, 0x0C, 0x00, 0x00};

u8 D_801E5A10[20] = "Pwr" T_END T_END T_END "Def" T_END T_END T_END "Agl";
