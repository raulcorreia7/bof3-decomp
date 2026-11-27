#include "engine/slus/slus.h"

/* routes a prompt selector byte: for work->unk_06 modes below 8 except 6 it latches D_801C839D[selector *
 * 2] into work->mirror, then by the context byte g_CurrentActor[0x95] sends the table byte through func_8014D8D4
 * (0xFF) or runs func_8014D6DC (table byte 5 or 6) or func_8014D6B8 while work[0x4B] differs. Mode 6 sends the selector
 * itself through func_8014D8D4.
 */
/* func_8015BAC4 */
MATCH void Script_DispatchSelector(u8 selector) {
    Actor* work;
    Actor* frame;
    u8     context;
    u8     table_byte;
    u16    table_word;
    s32    index;

    work = SELF(Actor);
    if (work->unk_06 < 8U) {
        if (work->unk_06 != 6) {
            work->mirror = D_801C839D[selector * 2];
            context      = g_CurrentActor[0x95];
            index        = selector * 2;
            if (context != GAME_NONE) {
                frame      = SELF(Actor);
                table_byte = D_801C839C[index];
                if (frame->script_record != table_byte) {
                    table_word = table_byte;
                    if ((u32)(table_word - 5) < 2) {
                        Script_Begin(table_byte, context);
                    } else {
                        Script_Select(table_byte);
                    }
                }
            } else {
                Script_Request(D_801C839C[index]);
            }
        } else {
            Script_Request(selector);
        }
    }
}
