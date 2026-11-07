#include "start_08.h"

/* The stat format strings the item, party and save panels print numbers with. */
char g_MenuStatFormat[4] = "%3d";
char g_MenuCurrentValueFormat[8] = "%3d/   ";
char g_MenuMaxValueFormat[8] = "   /%3d";
char g_MenuExperienceFormat[4] = "%8d";
char g_MenuExperienceBlank[12] = "--------";

char g_MenuZennyFormat[4] = "%7d";
char g_MenuNextExpBlank[8] = "-------";

/* The ten formation layouts of the party formation menu (Menu_DrawFormationPreview copies them to the stack). */
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
