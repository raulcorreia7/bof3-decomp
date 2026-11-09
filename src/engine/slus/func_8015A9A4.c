#include "engine/slus/slus.h"
#include <inline_c.h>

/* projects the record's position through the GTE into screen halfwords at +0x2E/+0x30 and a depth word at +0x60;
 * clears or sets the record's off-screen flag (bit 7 of the first byte) and registers on-screen records in D_8014828C.
 */
/* Reordered coordinate assignments leave the origin load difference at +0x0C; volatile reads and a barrier alter the prologue. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015A9A4(void) {
    s16   vec_x;
    s16   vec_y;
    s16   vec_z;
    s16   vec_pad;
    s16   sxy[2];
    s16   temp_a2_146;
    s32   temp_a0_142;
    s32   var_v0_28;
    s32   x_part;
    s32   var_v0_66;
    u16   temp_a0_51;
    u16   temp_v1_31;
    u16   var_v0_38;
    u32   temp_a0_192;
    void* temp_a1_132;
    void* temp_a1_42;
    void* temp_a2_15;
    void* temp_v1_177;
    void* temp_v1_96;

    temp_a2_15 = g_Task;
    x_part     = FIELD(s16, temp_a2_15, 0x36u) - g_AreaTileOriginX;
    var_v0_28  = FIELD(s16, temp_a2_15, 0x3Au) - g_AreaTileOriginY;
    if (FIELD(u16, temp_a2_15, 0x34u) != 0) {
        var_v0_28 += 1;
    }
    temp_v1_31 = x_part + var_v0_28;
    var_v0_38  = temp_v1_31 + 1;
    if (COORD_FRAC(g_Task->pos.y) == 0) {
        var_v0_38 = temp_v1_31;
    }
    temp_a1_42                    = g_Task;
    FIELD(u16, temp_a2_15, 0x32u) = var_v0_38;
    temp_a0_51 = (FIELD(u16, temp_a1_42, 0x32u) + (s8)FIELD(u8, (*(void**)((u8*)(temp_a1_42) + 0x54)), 0x1u)) << 8;
    FIELD(u16, temp_a1_42, 0x32u) = temp_a0_51;
    if (g_AreaDrawMode == 4) {
        if (D_8014933F != 0) {
            var_v0_66 = ((s32)FIELD(u16, temp_a1_42, 0x34u) >> 0xF) & BYTE_MASK;
        } else {
            var_v0_66 = ((s32)FIELD(u16, temp_a1_42, 0x38u) >> 0xF) & BYTE_MASK;
        }
    } else {
        var_v0_66 = (((u16)FIELD(u16, temp_a1_42, 0x3Eu) >> 5) & BYTE_MASK) ^ 0x80;
    }
    FIELD(u16, temp_a1_42, 0x32u) = (u16)(temp_a0_51 | var_v0_66);
    if (!(FIELD(u8, (*(void**)((u8*)(g_Task) + 0x54)), 0x3u) & 0x10)) {
        Actor_ReadValue();
    }
    temp_v1_96 = g_Task;
    vec_x      = ((s32)FIELD(u16, temp_v1_96, 0x34u) >> 9) - 0x4000;
    vec_y      = ((s32)FIELD(u16, temp_v1_96, 0x38u) >> 9) - 0x4000;
    vec_z      = (s16)((s16) - (s16)FIELD(u16, temp_v1_96, 0x3Eu) / 2);
    gte_ldv0(&vec_x);
    gte_rtps();
    gte_stsxy(sxy);
    gte_stszotz(&g_Task->unk_60);
    temp_a1_132                    = g_Task;
    FIELD(u16, temp_a1_132, 0x2Eu) = sxy[0];
    FIELD(u16, temp_a1_132, 0x30u) = sxy[1];
    temp_a0_142                    = ((u8)FIELD(u8, (*(void**)((u8*)(temp_a1_132) + 0x54)), 0x3u) >> 1) & 4;
    temp_a2_146                    = (s16)FIELD(u16, temp_a1_132, 0x2Eu);
    if ((((&D_80182174)[temp_a0_142] + 0x140) < temp_a2_146) || (temp_a2_146 < -(s32)(&D_80182175)[temp_a0_142]) ||
        (((&D_80182176)[temp_a0_142] + 0xF0) < sxy[1]) || (sxy[1] < -(s32)(&D_80182177)[temp_a0_142])) {
        temp_v1_177         = g_Task;
        *(u8*)(temp_v1_177) = (u8)(*(u8*)(temp_v1_177) | 0x80);
        return;
    }
    *(u8*)(temp_a1_132) = (u8)(*(u8*)(temp_a1_132) & 0x7F);
    temp_a0_192         = D_8014832D & BYTE_MASK;
    if (temp_a0_192 < 0x28U) {
        D_8014832D += 1;
        D_8014828C[temp_a0_192] = (s32)g_Task;
    }
}
#else
INCLUDE_ASM(func_8015A9A4);
#endif
