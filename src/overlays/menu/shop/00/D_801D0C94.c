#include "shop_00.h"

char D_801D0C94[4] = "*";

char D_801D0C98[0x44] = {
    0x82, 0x61, 0x82, 0x92, 0x82, 0x85, 0x82, 0x81, 0x82, 0x94, 0x82, 0x88, 0x81, 0x40, 0x82, 0x8F,
    0x82, 0x86, 0x81, 0x40, 0x82, 0x65, 0x82, 0x89, 0x82, 0x92, 0x82, 0x85, 0x81, 0x40, 0x82, 0x52,
    0x81, 0x69, 0x25, 0x73, 0x81, 0x6A, 0x81, 0x40, 0x25, 0x73, 0x25, 0x73, 0x82, 0x88, 0x25, 0x73,
    0x25, 0x73, 0x82, 0x8D, 0x81, 0x40, 0x82, 0x6B, 0x82, 0x96, 0x81, 0x44, 0x25, 0x73, 0x25, 0x73,
    0x00, 0x65, 0x70, 0x74,
};

char D_801D0CDC[4] = "%3dZ";
u8   D_801D0CE0[4] = {0x00, 0x94, 0x08, 0x00};
char g_MenuStatFormat[4] = "%3d";
char g_MenuCurrentValueFormat[8] = "%3d/   ";
char g_MenuMaxValueFormat[8] = "   /%3d";
char g_MenuExperienceFormat[4] = "%8d";
char g_MenuExperienceBlank[12] = "--------";
char g_MenuZennyFormat[4] = "%7d";
char g_MenuNextExpBlank[8] = "-------";

/* The ten formation layouts the party formation menu offers (Menu_DrawFormationPreview copies them to the stack). */
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
