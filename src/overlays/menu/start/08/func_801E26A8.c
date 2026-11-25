#include "start_08.h"

/* One config row's option and its current value. */
typedef struct {
    u8 option;
    u8 value;
} ConfigPair;

/* Draws the config window: the frame and six option rows, the selected row with its value. */
MATCH void func_801E26A8(s32 x, s32 y) {
    ConfigPair pairs[6] = {{0, g_MessageSpeed}, {1, g_WindowStyle}, {2, g_WindowClut}, {3, g_SndMono}, {4, g_AutoRun}, {5, 0}};
    u16        left;
    s32        row;
    s16        i;

    Menu_DrawWindowFrame((s16)x, (s16)y, 0x21, 0xD);
    left = x + 5;
    row  = y + 9;
    for (i = 0; i < 6; i++, row += 0xF) {
        Menu_DrawConfigRow(left, (u16)row, i & BYTE_MASK, (s8)g_ConfigSelect[1] - 2 == i ? g_ConfigSelect[0] : 0);
        func_801E2C00(left, (u16)row, pairs[i].option, pairs[i].value, (s8)g_ConfigSelect[1] - 2 == i ? g_ConfigSelect[0] : 0);
    }
}
