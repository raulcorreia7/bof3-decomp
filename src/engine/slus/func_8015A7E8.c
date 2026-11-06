#include "engine/slus/slus.h"

/* publishes each of the four 0x98-byte work records, honouring the
 *           record flag and dispatching the mode table for active records.
 */
MATCH void func_8015A7E8(void) {
    u8* rec;
    u8* base;
    u32 i;
    u32 off;
    u8  ctrl;

    rec = (u8*)D_80147A58;
    i   = 0;
    for (base = rec; (i & 0xFF) < 4; i++, rec += ACTOR_SIZE) {
        g_Task         = rec;
        g_CurrentActor = rec;
        if ((rec[0] & 1) == 0) {
            continue;
        }
        if (rec[9] == 0) {
            off  = (i & 0xFF) * ACTOR_SIZE;
            ctrl = D_80147ACC[off];
            if ((ctrl & 0x20) != 0) {
                if ((ctrl & LZ77_CONTROL_LITERAL_FLAG) != 0) {
                    func_801A17A0(off + D_80147ACC);
                } else {
                    func_801A18C8((u8*)((i & 0xFF) * ACTOR_SIZE + (u32)base));
                }
                continue;
            }
        }
        if ((g_CurrentActor[0x74] & ACTOR_FLAG_INTERACTION_PENDING) != 0) {
            func_801A3A08();
            continue;
        }
        D_801C83D8[TASK_BYTES[1]]((u8*)((i & 0xFF) * ACTOR_SIZE + (u32)base));
    }
}
