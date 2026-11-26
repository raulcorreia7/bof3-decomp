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

    rec = (u8*)g_PartyActors;
    i   = 0;
    for (base = rec; (i & BYTE_MASK) < 4; i++, rec += ACTOR_SIZE) {
        SELF_SET(rec);
        g_CurrentActor = rec;
        if ((rec[0] & 0x1) == 0) {
            continue;
        }
        if (rec[9] == 0) {
            off  = (i & BYTE_MASK) * ACTOR_SIZE;
            ctrl = g_PartyActors[i & BYTE_MASK].interaction_flags;
            if ((ctrl & 0x20) != 0) {
                if ((ctrl & LZ77_CONTROL_LITERAL_FLAG) != 0) {
                    func_801A17A0((u8*)&g_PartyActors[i & BYTE_MASK].interaction_flags);
                } else {
                    func_801A18C8((u8*)((i & BYTE_MASK) * ACTOR_SIZE + (u32)base));
                }
                continue;
            }
        }
        if ((g_CurrentActor[0x74] & ACTOR_INTERACTION_PENDING) != 0) {
            func_801A3A08();
            continue;
        }
        g_ActorModes[SELF(Actor)->header.mode]((u8*)((i & BYTE_MASK) * ACTOR_SIZE + (u32)base));
    }
}
