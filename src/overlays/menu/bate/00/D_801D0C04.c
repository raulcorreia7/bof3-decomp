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
char g_MenuExperienceFormat[4] = "%8d";
char g_MenuExperienceBlank[12] = "--------";
char g_MenuZennyFormat[4] = "%7d";
char g_MenuNextExpBlank[8] = "-------";
FormationLayout g_MenuFormations[FORMATION_COUNT] = {
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
FormationOrder g_MenuFormationOrder = {{0, 1, 2}};
char g_MenuClockFormat[12] = "%02d";
