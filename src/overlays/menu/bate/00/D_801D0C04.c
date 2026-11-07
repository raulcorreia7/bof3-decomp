#include "bate_00.h"

/* The format strings, the ten formation layouts of the party formation menu, and the address runs ahead of the code. */
static char s_gap_801D0C04[8] = "  %3d";
static char s_gap_801D0C0C[8] = " ---";
static char s_gap_801D0C14[4] = "---";
static char s_gap_801D0C18[4] = "%7d";
static char s_gap_801D0C1C[4] = "%4d";
char g_MenuStatFormat[4] = "%3d";
static char s_gap_801D0C24[8] = "%3d/   ";
static char s_gap_801D0C2C[8] = "   /%3d";
static char s_gap_801D0C34[4] = "%8d";
static char s_gap_801D0C38[12] = "--------";
char g_MenuZennyFormat[4] = "%7d";
char g_MenuNextExpBlank[8] = "-------";
FormationLayout g_BateFormations[FORMATION_COUNT] = {
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
u8 D_801D0D18[4] = {0, 1, 2};
char g_MenuClockFormat[12] = "%02d";
static u8 s_gap_801D0D28[52] = {
    0xD8, 0x5F, 0x1D, 0x80, 0xE0, 0x5F, 0x1D, 0x80, 0xE8, 0x5F, 0x1D, 0x80, 0xE8, 0x5F, 0x1D, 0x80,
    0xE8, 0x5F, 0x1D, 0x80, 0xF0, 0x5F, 0x1D, 0x80, 0xD8, 0x5F, 0x1D, 0x80, 0xD8, 0x5F, 0x1D, 0x80,
    0xD8, 0x5F, 0x1D, 0x80, 0xD8, 0x5F, 0x1D, 0x80, 0xF0, 0x5F, 0x1D, 0x80, 0xF0, 0x5F, 0x1D, 0x80,
    0xD8, 0x5F, 0x1D, 0x80,
};
char g_MenuInventoryCountFormat[8] = "%3d/%3d";
static u8 s_gap_801D0D64[4] = {
    0x00, 0x00, 0x00, 0x00,
};
static u8 s_gap_801D0D68[24] = {
    0x24, 0x7B, 0x1D, 0x80, 0x2C, 0x7B, 0x1D, 0x80, 0x2C, 0x7B, 0x1D, 0x80, 0x2C, 0x7B, 0x1D, 0x80,
    0x34, 0x7B, 0x1D, 0x80, 0x34, 0x7B, 0x1D, 0x80,
};
u8 D_801D0D80[4] = "%2d";
u8 D_801D0D84[12] = "%02d %02d";
u8 D_801D0D90[4] = "  :";
u8 D_801D0D94[4] = "1";
u8 D_801D0D98[4] = {
    0x32, 0x00, 0x66, 0x61,
};
