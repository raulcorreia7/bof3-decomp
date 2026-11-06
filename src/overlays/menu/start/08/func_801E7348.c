#include "start_08.h"

MATCH s32 func_801E7348(void) {
    u8   buffer[2];
    u8   count;
    u8   matched;
    u8   total;
    u8   i;
    u32  value;
    u32  shift;
    s32  masked;
    s32  bumped;
    u32* count_word;

    buffer[1] = 0;
    buffer[0] = 0;
    for (g_SaveCardPort = 0; g_SaveCardPort < 2; g_SaveCardPort++) {
        CardAccessFile(0, 0, 0, 0, 0);
        if (g_SaveCardStatus == CARD_EVENT_OK || g_SaveCardStatus == CARD_EVENT_NEW) {
            count   = func_801EFCA8(D_801D0F14, 0x10);
            matched = 0;
            total   = 0;
            /* Each 0x18-byte save row holds a name and its packed count word at 0x14. */
            for (i = 0; i < count; i++) {
                if (strncmp((char*)(D_8018E990 + i * 0x18), g_SaveFileNameFormat, 0x10) == 0) {
                    matched += 1;
                }
                count_word = (u32*)((u8*)&D_8018E9A4 + i * 0x18);
                value      = *count_word;
                shift      = value >> 13;
                masked     = total & BYTE_MASK;
                if ((value & 0x1FFF) != 0) {
                    bumped = masked + 1;
                    total  = bumped + shift;
                } else {
                    total = masked + shift;
                }
            }
            if (matched == 0) {
                if (total == 15) {
                    buffer[g_SaveCardPort] = 3;
                } else {
                    buffer[g_SaveCardPort] = 1;
                }
            }
        } else {
            buffer[g_SaveCardPort] = 2;
        }
    }
    return buffer[1] | (buffer[0] << 8);
}
