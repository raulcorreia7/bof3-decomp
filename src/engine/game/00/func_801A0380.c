#include "game_00.h"

MATCH void func_801A0380(s16 x, s16 y, u16 kind) {
    u8* cursor;
    u8* entry;
    s32 done;
    u8* record;
    u8  result;
    s32 count;
    s32 limit;
    u8* table;
    s32 index;
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);

    if (g_GameFlags & 0x80) {
        result = g_SaveData.snd_bgm_id;
    } else {
        record = func_801A0490(x, y, kind);
        if (record[7] == 0) {
            result = record[6];
        } else {
            index = record[6] << 3;
            count = D_80181E44[index];
            /* FAKE: statement boundary keeps the retail register order and schedule. */
            ORDER_LOCK(done = 0);
            entry = *(u8**)(D_80181E40 + index);
            if (count > 0) {
                table  = g_SaveData.scene_flag_words;
                limit  = count;
                cursor = entry + 2;
                do {
                    if (SYS_TestFlag((void*)((*(cursor - 1) * 8) + (u32)table), *cursor) != 0) {
                        break;
                    }
                    done += 1;
                    cursor += 3;
                    entry += 3;
                } while (done < limit);
            }
            result = *entry;
        }
    }
    g_GamePrevSelection = result;
}
