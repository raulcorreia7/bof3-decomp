#include "slus.h"

/*
 * callback table read by func_80155B40, handler table D_8017F8F0 and
 * the small value tables read by func_80157CE4 and func_80159580.
 */

const CellFunc D_8017F668[77] = {
    (CellFunc)Area_DrawPartQuads,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015684C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_801569B8,
    (CellFunc)Area_DrawPartAnimation,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    (CellFunc)func_8015763C,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    func_80156E00,
    (CellFunc)func_8015763C,
    (CellFunc)Area_DrawGouraudQuads,
    Area_DrawParts,
    (CellFunc)func_8015763C,
    (CellFunc)func_80157644,
    (CellFunc)func_801576A0,
    (CellFunc)func_8015763C,
    Area_DrawSceneSprite,
    (CellFunc)&D_801EFEFC,
    (CellFunc)&D_801F016C,
    (CellFunc)&D_801F0488,
    (CellFunc)&D_801F0778,
    (CellFunc)func_8015763C,
    (CellFunc)func_8015763C,
    (CellFunc)func_8015763C,
    (CellFunc)func_8015763C,
    (CellFunc)func_8015763C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015684C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_8015642C,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
    func_80157CE4,
};

const u8 g_SpriteCellPartCounts[12] = {
    0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00,
};

const s16 D_8017F7A8[54] = {
    -247, -66, 181, -181, 66, 247, -256, 0,   0,   256,  0,  0,   -123, -33, 90, -90, 33, 123,
    -123, -33, 90,  -90,  33, 123, -247, -66, 181, -181, 66, 247, -123, -33, 90, -90, 33, 123,
    -247, -66, 181, -181, 66, 247, -247, -66, 181, -181, 66, 247, -123, -33, 90, -90, 33, 123,
};

const s16 D_8017F814[54] = {
    -66, -247, -181, 181, 247, 66, 0,   -256, 256,  0,   0,   0,  -33, -123, -90, 90, 123, 33,
    -33, -123, -90,  90,  123, 33, -66, -247, -181, 181, 247, 66, -33, -123, -90, 90, 123, 33,
    -66, -247, -181, 181, 247, 66, -66, -247, -181, 181, 247, 66, -33, -123, -90, 90, 123, 33,
};

const u16 D_8017F880[10] = {
    0x0200, 0x0200, 0x0100, 0x0080, 0x0280, 0x0100, 0x0200, 0x0200, 0x0100, 0x0000,
};

const u8 g_SpriteCellTopV[20] = {
    0x00, 0x3F, 0x00, 0x3F, 0x00, 0x1F, 0x20, 0x3F, 0x50, 0x8F,
    0x20, 0x3F, 0x50, 0x8F, 0x00, 0x3F, 0x00, 0x1F, 0x00, 0x00,
};

const u8 g_SpriteCellBottomV[20] = {
    0x1F, 0x20, 0x1F, 0x20, 0x0F, 0x10, 0x2F, 0x30, 0x6F, 0x70,
    0x2F, 0x30, 0x6F, 0x70, 0x1F, 0x20, 0x0F, 0x10, 0x00, 0x00,
};

const u8 g_SpriteCellLeftU[12] = {
    0x00, 0x00, 0x40, 0x50, 0x00, 0x40, 0x50, 0x00, 0x40, 0x00, 0x00, 0x00,
};

const u8 g_SpriteCellRightU[12] = {
    0x3F, 0x3F, 0x5F, 0x5F, 0x4F, 0x5F, 0x8F, 0x3F, 0x5F, 0x00, 0x00, 0x00,
};

const u8 g_SpriteCellCluts[12] = {
    0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const u32 D_8017F8E0[4] = {
    0xB1800007,
    0xB1810007,
    0xBD800006,
    0xBD810006,
};

const ObjectFunc D_8017F8F0[7] = {
    (ObjectFunc)Area_ReadTintRecord,  func_801583BC, (ObjectFunc)Area_WriteCellRecord, (ObjectFunc)Area_LoadPaletteBank,
    (ObjectFunc)Area_DrawGouraudQuad, func_80158830, func_80158940,
};

const u8 g_MenuPanelOrigins[32] = {
    0x3C, 0xAA, 0x3C, 0x5D, 0x3C, 0x18, 0x10, 0x18, 0x68, 0x18, 0x10, 0xAA, 0x68, 0xAA, 0x00, 0x00,
    0x64, 0xAA, 0x64, 0x5D, 0x64, 0x18, 0x10, 0x18, 0xB8, 0x18, 0x10, 0xAA, 0xB8, 0xAA, 0x00, 0x00,
};

const u16 D_8017F92C[2] = {
    0x0000,
    0x0000,
};

const u16 D_8017F930[10] = {
    0x0036, 0x002C, 0x0030, 0x0052, 0x00DC, 0x0044, 0x0030, 0x0018, 0x00DC, 0x00C0,
};

const u16 D_8017F944[7][2] = {
    {0x00BC, 0x0082}, {0x00BC, 0x009E}, {0x00BC, 0x0056}, {0x0091, 0x0056},
    {0x00E2, 0x0056}, {0x0091, 0x0082}, {0x00E2, 0x0082},
};

const WindowTextRow D_8017F960[3] = {
    {8, 2, 16},
    {8, 2, 30},
    {8, 2, 30},
};

const u16 D_8017F972 = 0;
