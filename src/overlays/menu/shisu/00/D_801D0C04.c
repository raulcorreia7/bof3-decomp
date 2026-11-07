#include "shisu_00.h"

/* The format strings, the ten formation layouts of the party formation menu, and the address runs ahead of the code. */
char g_MenuStatFormat[4] = "%3d";
static char s_gap_801D0C08[8] = "%3d/   ";
static char s_gap_801D0C10[8] = "   /%3d";
static char s_gap_801D0C18[4] = "%8d";
static char s_gap_801D0C1C[12] = "--------";
char g_MenuZennyFormat[4] = "%7d";
char g_MenuNextExpBlank[8] = "-------";
FormationLayout g_ShisuFormations[FORMATION_COUNT] = {
    {"Normal", 6, {{0, 0}, {0, 0}, {0, 0}}},
    {"Normal", 6, {{-8, -8}, {8, -8}, {0, 0}}},
    {"Attack", 6, {{0, -8}, {0, 8}, {0, 0}}},
    {"Defense", 7, {{-4, 0}, {4, 0}, {0, 0}}},
    {"Normal", 6, {{-8, -8}, {8, -8}, {0, 8}}},
    {"Attack", 6, {{0, -8}, {-8, 8}, {8, 8}}},
    {"Defense", 7, {{0, 0}, {-8, 0}, {8, 0}}},
    {"Chain", 5, {{-4, -12}, {0, 0}, {4, 12}}},
    {"Magic", 5, {{-12, -4}, {12, -4}, {0, 4}}},
    {"Refuge", 6, {{0, -12}, {-8, 0}, {8, 12}}},
};
u8 D_801D0CFC[4] = {0, 1, 2};
char g_MenuClockFormat[12] = "%02d";
static u8 s_gap_801D0D0C[52] = {
    0x80, 0x6F, 0x1D, 0x80, 0x88, 0x6F, 0x1D, 0x80, 0x90, 0x6F, 0x1D, 0x80, 0x90, 0x6F, 0x1D, 0x80,
    0x90, 0x6F, 0x1D, 0x80, 0x98, 0x6F, 0x1D, 0x80, 0x80, 0x6F, 0x1D, 0x80, 0x80, 0x6F, 0x1D, 0x80,
    0x80, 0x6F, 0x1D, 0x80, 0x80, 0x6F, 0x1D, 0x80, 0x98, 0x6F, 0x1D, 0x80, 0x98, 0x6F, 0x1D, 0x80,
    0x80, 0x6F, 0x1D, 0x80,
};
char g_MenuInventoryCountFormat[8] = "%3d/%3d";
static u8 s_gap_801D0D48[4] = {
    0x00, 0x00, 0x00, 0x00,
};
static u8 s_gap_801D0D4C[24] = {
    0xCC, 0x8A, 0x1D, 0x80, 0xD4, 0x8A, 0x1D, 0x80, 0xD4, 0x8A, 0x1D, 0x80, 0xD4, 0x8A, 0x1D, 0x80,
    0xDC, 0x8A, 0x1D, 0x80, 0xDC, 0x8A, 0x1D, 0x80,
};
char D_801D0D64[4] = "%2d";
char D_801D0D68[12] = "%02d %02d";
char D_801D0D74[4] = "  :";
char D_801D0D78[4] = "1";
char D_801D0D7C[4] = {
    0x32, 0x00, 0x00, 0x0D,
};
