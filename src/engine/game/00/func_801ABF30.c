#include "game_00.h"

/* Scratchpad spill slot for the incoming work pointer while the call runs. */
#define SAVE_SLOT SP_REF(Actor*, 0x10u)

MATCH VECTOR* func_801ABF30(VECTOR* out, s32 sel, s32 selector_kind) {
    Actor* work;
    Actor* cur;
    VECTOR buf;
    u8     i;
    u8     count;
    u8     key;

    SAVE_SLOT = g_Task;
    key       = sel;
    if ((sel & 0x80) != 0) {
        key &= 0x3F;
        i     = 0;
        count = 0;
        for (; i < ENTITY_MAX; i++) {
            if (g_Actors[i].unk_06 == 0x0A) {
                if (count == key) {
                    break;
                }
                count += 1;
            }
        }
        work = &g_Actors[count];
    } else {
        work = &D_80147A58[key];
    }
    g_Task = work;
    /* FAKE: keeps the scratchpad store ahead of the call-argument setup. */
    MATCH_BARRIER();
    func_801AC1DC((s32*)&buf.vx, selector_kind);
    cur = g_Task;
    buf.vx += cur->x.fixed;
    buf.vy += cur->y.fixed;
    buf.vz += (s16)cur->z.part.integer;
    g_Task = SAVE_SLOT;
    *out   = buf;
    return out;
}
