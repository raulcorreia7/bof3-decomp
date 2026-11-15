#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3BC0(void) {
    u8  col;
    u8  facing;
    u8  i;
    s32 nibble;
    u8  row;
    u8* table;
    u8  index;

    col    = (g_Task->pos.x.part.integer - 0xB) >> 1;
    row    = (g_Task->pos.y.part.integer - 0xB1) >> 1;
    facing = g_Task->direction_08 & 7;
    index  = facing * 2;
    table  = D_801F5C18;
    i      = 0;
    while (1) {
        col += D_80181B00[index];
        if (col >= 7) {
            break;
        }
        row += D_80181B01[index];
        if (row >= 7) {
            break;
        }
        if (col & 1) {
            nibble = table[(s8)row * 4 + (s8)col / 2] & 0xF;
        } else {
            nibble = table[(s8)row * 4 + (s8)col / 2] >> 4;
        }
        if (nibble == 0xF) {
            break;
        }
        i += 4;
    }
    if (i == 0) {
        return;
    }
    g_ScriptState->unk_07 = i + 1;
    func_801C5DFC(g_Task->direction_08);
    g_ScriptState->flag_00 |= 0x40;
    g_AreaCameraHeightStep     = 0;
    g_Task->vz                 = 0;
    g_Task->pos.z.part.integer = -0x500;
}
#else
INCLUDE_ASM(func_801F3BC0);
#endif
