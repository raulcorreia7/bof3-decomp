#include "area086_13.h"

MATCH s32 func_801F3350(s32 x, s32 y) {
    s32 i;
    s32 entry;
    s32 rect;
    s32 scan;
    s32 cell_x;
    s32 cell_y;
    u8* facing;

    i = 0;
    x &= BYTE_MASK;
    y &= BYTE_MASK;
    facing = &g_Game.members[0].facing;
    entry  = 0;
    for (; i < 3; i++, entry += 4) {
        if (x == D_801F3CEC[entry] && y == D_801F3CED[entry] && D_801F3CEE[entry] == *facing) {
            break;
        }
    }
    if (i == 3) {
        return 0;
    }
    rect   = i * 4;
    cell_x = D_801F3CF8[rect];
    if (cell_x < D_801F3CFA[rect]) {
        do {
            cell_y = D_801F3CF9[rect];
            if (cell_y < D_801F3CFB[rect]) {
                scan = rect;
                do {
                    if ((s8)Area_FindMemberAt(cell_x, cell_y) >= 0) {
                        return 0;
                    }
                    cell_y++;
                } while (cell_y < D_801F3CFB[scan]);
            }
            cell_x++;
            rect = i * 4;
        } while (cell_x < D_801F3CFA[rect]);
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F3CEF[i * 4]);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
    Scene_StartToggleLock(0xF);
    return 1;
}
