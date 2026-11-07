#include "start_08.h"

/* The stat format strings the item, party and save panels print numbers with. */
char g_MenuStatFormat[4] = "%3d";
char g_MenuCurrentValueFormat[8] = "%3d/   ";
char g_MenuMaxValueFormat[8] = "   /%3d";
char g_MenuExperienceFormat[4] = "%8d";
char g_MenuExperienceBlank[12] = "--------";

char g_MenuZennyFormat[4] = "%7d";
char g_MenuNextExpBlank[8] = "-------";

/* The ten formation layouts of the party formation menu (the shop image holds the reader). */
FormationLayout g_StartFormations[FORMATION_COUNT] = {
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

u8 D_801D0D44[4] = {0, 1, 2};

char g_MenuClockFormat[12] = "%02d";

/* 0x801D0D54: two runs of image addresses (13 words at 0x801D0D54, 6 at 0x801D0D94) with the "%3d/%3d" format between
   them. No reader found. */
static u8 s_gap_801D0D54[52] = {
    0x78, 0xEF, 0x1D, 0x80, 0x80, 0xEF, 0x1D, 0x80, 0x88, 0xEF, 0x1D, 0x80, 0x88, 0xEF, 0x1D, 0x80,
    0x88, 0xEF, 0x1D, 0x80, 0x90, 0xEF, 0x1D, 0x80, 0x78, 0xEF, 0x1D, 0x80, 0x78, 0xEF, 0x1D, 0x80,
    0x78, 0xEF, 0x1D, 0x80, 0x78, 0xEF, 0x1D, 0x80, 0x90, 0xEF, 0x1D, 0x80, 0x90, 0xEF, 0x1D, 0x80,
    0x78, 0xEF, 0x1D, 0x80,
};
char g_MenuInventoryCountFormat[8] = "%3d/%3d";
static u8 s_gap_801D0D90[4] = {0x00, 0x00, 0x00, 0x00};
