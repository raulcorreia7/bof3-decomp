#include "engine/slus/slus.h"

/* routes a prompt selector byte. */
MATCH void func_8015BAC4(u8 selector) {
    Actor* work;
    Actor* frame;
    u8     context;
    u8     table_byte;
    u16    table_word;
    s32    index;

    work = g_Task;
    if (work->unk_06 < 8U) {
        if (work->unk_06 != 6) {
            work->unk_2A = D_801C839D[selector * 2];
            context      = g_CurrentActor[0x95];
            index        = selector * 2;
            if (context != GAME_NONE) {
                frame      = g_Task;
                table_byte = D_801C839C[index];
                if (frame->unk_4B != table_byte) {
                    table_word = table_byte;
                    if ((u32)(table_word - 5) < 2) {
                        Actor_BeginScript(table_byte, context);
                    } else {
                        Actor_SelectScript(table_byte);
                    }
                }
            } else {
                Actor_RequestScript(D_801C839C[index]);
            }
        } else {
            Actor_RequestScript(selector);
        }
    }
}
