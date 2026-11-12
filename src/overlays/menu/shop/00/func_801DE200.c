#include "shop_00.h"

MATCH void func_801DE200(void) {
    /* FAKE: retail reserves 0x18 frame bytes no statement touches (only ra at
     * 0x28 is accessed); no struct, array or argument explains them. */
    FAKE_STACK_PADS(u8, 24);
    s32 party_count;
    s32 search_limit;
    s32 count;
    s32 flag_index;
    s32 standby_index;
    s32 record_offset;
    /* FAKE: retail homes the inner search index in $v1; gcc 2.7.2 assigns the
     * opposite pair without a pin. */
    FAKE_REG(s32, order_index, "v1");
    /* FAKE: retail homes the flag counter in $v1; the flag loop and the
     * standby loop share that home. */
    FAKE_REG(s32, marked, "v1");
    s32 clear_index;
    /* FAKE: retail homes the standby counter in $v1; gcc 2.7.2 assigns the pair
     * swapped. */
    FAKE_REG(s32, standby_count, "v1");
    u8* record;
    u8  standby_total;
    s32 limit;
    u8  flag_value;
    u8  standby_value;
    s32 total;

    /* The retail copies the whole $v0 (move t1,v0); shop_00.h declares
     * Party_CountOrder as u8(u8), so the call is made through a word-typed
     * pointer. */
    count         = ((s32 (*)(u8))Party_CountOrder)(0);
    search_limit  = count & BYTE_MASK;
    record        = &g_Characters[0].character_id;
    record_offset = 0;
    D_801E6250    = 0;
    do {
        order_index = 0;
        if (((u8*)&g_Characters[0].unk_07)[record_offset] & 0x1) {
            limit = search_limit;
            if (search_limit != 0) {
            loop_4:
                if (*record != g_PartyFieldOrder[order_index]) {
                    order_index += 1;
                    if (order_index < limit) {
                        goto loop_4; /* retail branch */
                    }
                }
            }
            if (order_index == search_limit) {
                standby_total                         = D_801E6250;
                D_801E6250                            = standby_total + 1;
                D_801E6244[standby_total & BYTE_MASK] = *record;
            }
        }
        record += 0xA4;
        record_offset += 0xA4;
    } while ((s32)record < (s32)&g_Characters[CHARACTER_COUNT].character_id);
    party_count = count & BYTE_MASK;
    marked      = 0;
    if (party_count > 0) {
        flag_value = 1;
        flag_index = 0;
        do {
            D_801E6248[flag_index] = flag_value;
            marked += 1;
            flag_index += 2;
        } while (marked < party_count);
    }
    if (marked < 3) {
        clear_index = marked * 2;
        do {
            D_801E6248[clear_index] = 0;
            clear_index += 2;
        } while (clear_index < 6);
    }
    standby_count = 0;
    total         = D_801E6250;
    if (total > 0) {
        standby_value = 1;
        standby_index = 0;
        do {
            D_801E6249[standby_index] = standby_value;
            standby_index += 2;
        } while (++standby_count < D_801E6250);
    }
    D_8014865A = 0x7F;
    D_8014865D = 0x7F;
    D_801E6254 = 0xFF;
    D_80148658 = 0;
    D_80148659 = 0;
    D_80148654 = 3;
    D_80148652 += 1;
    UI_SetMode(2U);
}
