#include "engine/slus/slus.h"

/* walks a message control stream (the switch is on the control byte) and draws the stream it describes: control
 * bytes 1, 3-9 select the glyph source (item, character or party tables) and advance the cursor; returns the stream
 * position after the last byte it consumed.
 */
#ifdef NON_MATCHING
NON_MATCHING u8* UI_DrawTextAt(s32 x, s32 y, u8* stream) {
    s32 temp_v0_136;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0_130;
    u8* var_s0;
    u8* var_s2;
    u8  temp_v1_122;
    u8  temp_v1_32;
    u8  var_s5;

    var_s0 = stream;
    var_s7 = x;
    var_s6 = y;
    var_s1 = 0;
    var_s2 = NULL;
    var_s3 = 0;
    var_s5 = 0;
    var_s4 = var_s7;
loop_1:
    temp_v1_32 = *var_s0;
    switch (temp_v1_32) {
        case 1:
            var_s4 = var_s7;
            var_s6 += 0xD;
        case 9:
        block_20:
            var_s0 += 1;
            goto loop_1;
        case 7:
            var_s1 |= 1;
            var_s0 += 1;
            var_s2 = var_s0;
            var_s3 = 0x20;
            var_s0 = (*var_s2 << 5) + &D_801490D7;
            goto block_20;
        case 3:
            var_s1 |= 1;
            var_s2 = var_s0;
            var_s0 = &D_80145F03;
            var_s0 = &D_80145F03;
            var_s3 = 5;
            goto block_20;
        case 4:
            var_s1 |= 1;
            var_s0 += 1;
            var_s2 = var_s0;
            var_s3 = 5;
            var_s0 = (*var_s2 * PARTY_RECORD_STRIDE) + &D_80144967;
            goto block_20;
        case 5:
            var_s0 += 1;
            var_s5 = *var_s0;
            var_s0 += 1;
            goto loop_1;
        case 6:
            var_s5 = 0;
            goto block_20;
        case 8:
            var_s1 |= 1;
            var_s0 += 1;
            var_s2 = var_s0;
            var_s0 = D_80010004 + SLUS_LOAD_ADDRESS;
            var_s3 = 0x10;
            var_s0 = &var_s0[*((*var_s2 * 2) + var_s0)];
            goto block_20;
        default:
            UI_DrawText((s16)var_s4, (s16)var_s6, (s32)var_s5, 1U, var_s0);
            temp_v1_122 = *var_s0;
            if (((u32)(temp_v1_122 - 0x12) < 2U) || (var_v0_130 = var_s1 & 1, ((temp_v1_122 & BYTE_MASK) == 0x15))) {
                var_s0 += 1;
                var_v0_130 = var_s1 & 1;
            }
            temp_v0_136 = var_s3 - 1;
            if (var_v0_130 != 0) {
                var_s3 = temp_v0_136;
                if (!(temp_v0_136 & BYTE_MASK)) {
                    var_s0 = var_s2;
                    var_s1 &= 0xFE;
                }
            }
            var_s4 += 8;
            goto block_20;
    }
    var_s1 &= 0xFE;
    if (var_s1 & 1) {
        var_s0 = var_s2;
        var_s2 = var_s0 + 1;
        goto block_20;
    }
    return var_s0 + 1;
}
#else
INCLUDE_ASM(UI_DrawTextAt);
#endif
