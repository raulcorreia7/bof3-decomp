#include "area030_04.h"

/* Draws the catch page for pond slot D_801E3208 (fish id and
 * length) and, on a 0x50 pad press, resolves the catch: fish 0x16 sets
 * message 1, a failed inventory add of item fish + 0x38 sets message 2,
 * and a successful add jumps the state (unk_03) to 0xD; then queues cue
 * 0x102 and advances the state. */
MATCH void func_801DBBAC(void) {
    u16 fish;
    s32 offset;

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[D_801E3208 * 0x98]);
    offset = D_801E3208 * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    func_801E1320(0xB0, 0x9C);
    func_801E1C7C();

    if (g_InputPressed & (PADRup | PADRdown)) {
        D_801E3214                    = 0;
        FISHING_STATE->saved_index_0B = 0;
        /* pond record +6 (fish id), read through the table base: the
         * D_8014688E spelling lets gcc hold its address across the calls */
        /* FAKE: retail reads g_Actors as u8[]. */
        fish                          = ((u8*)g_Actors)[D_801E3208 * 0x98 + 6];
        if ((u8)fish == 0x16) {
            FISHING_STATE->step_timer_09  = 4;
            FISHING_STATE->saved_index_0B = 1;
        } else if (!(Party_AddItem(ITEM_CAT_ITEM, (fish + 0x38) & BYTE_MASK, 1, 0) & BYTE_MASK)) {
            FISHING_STATE->step_timer_09  = 4;
            FISHING_STATE->saved_index_0B = 2;
        } else {
            FISHING_STATE->sub_index_03 = 0xD;
        }
        SND_PlayCue(EMI_CUE_ID(1, 2));
        FISHING_STATE->sub_index_03++;
    }
    func_8014D978();
    func_801E16DC();
}
