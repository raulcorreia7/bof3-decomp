#include "game_00.h"

MATCH void func_801B0C88(void) {
    s32 index;
    s32 total;
    u8  sel;
    s32 flag;
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    total = Party_CountOrder(PARTY_ORDER_FIELD);
    index = 0;
    if ((total & BYTE_MASK) > 0) {
        do {
            sel = g_CharSlot[g_PartyFieldOrder[index]];
            if (g_Characters[sel].status & STATUS_POISONED) {
                /* party member is active: use mode 3 */
                goto store3;
            }
            index++;
        } while (index < (total & BYTE_MASK));
    }
    if (!(g_Game.flags & 0x200)) {
        flag = g_AutoRun;
        if (g_Game.input & g_InputMasks[FIELD_INPUT_RUN]) {
            if ((flag ^ 0x1) == 0) {
                /* confirm pressed with the flag set: use mode 3 */
                goto store3;
            }
        } else {
            if (flag == 0) {
                /* nothing pressed with the flag clear: use mode 3 */
                goto store3;
            }
        }
    check_button:
        if (!(g_Game.walk_flags & 0x20)) {
            g_Game.current->u.field.counter_11C.s8_value = 4;
            return;
        }
    store3:
        g_Game.current->u.field.counter_11C.s8_value = 3;
    }
}
