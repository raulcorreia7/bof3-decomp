#include "area030_04.h"

FishingAnchors D_801D0C30 = {
    {
        {0x68, 0x42},
        {0x20, 0x70},
        {-32, 0x70},
    },
};

char D_801D0C38[] = "%3d";

/* The roster panel icon rows, read by Fishing_DrawRank: icon id, x offset and the two marker flags, 13 rows. */
FishingIconData g_FishingRankIcons = {
    {
        {8, 56, 0, 0},
        {8, 56, 1, 0},
        {8, 56, 1, 1},
        {9, 58, 0, 0},
        {9, 58, 1, 0},
        {9, 58, 1, 1},
        {10, 73, 0, 0},
        {10, 73, 1, 0},
        {10, 73, 1, 1},
        {11, 78, 0, 0},
        {11, 78, 1, 0},
        {11, 78, 1, 1},
        {73, 40, 0, 0},
    },
};

/* The count thresholds that pick the roster row, read by Fishing_DrawRank: 13 halfwords ending in 0xFFFF; the struct is
   padded to a word. */
FishingThreshold D_801D0C70 = {
    {100, 300, 500, 1000, 1500, 2000, 3000, 4000, 5000, 7000, 9000, 9500, 0xFFFF},
};

u8 D_801D0C8C[4] = {0x25, 0x34, 0x64, 0x00};
