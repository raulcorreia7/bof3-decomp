#include "batl_end_00.h"

/* Party item grant queue at D_80146327: the count byte, an unaligned run of
 * item words at +0xD and each item's level byte at +0x2D. */
typedef struct PartyGrantQueue {
    u8 count; /* +0x00 */
    u8 pad_01[0xC];
    u8 items[32];  /* +0x0D u16 item words */
    u8 levels[16]; /* +0x2D */
} PartyGrantQueue;

extern PartyGrantQueue D_80146327;

/* func_801EF870 */
MATCH void Battle_GrantQueuedItems(void) {
    u8  slot;
    u16 item;

    if (EMI_LoaderIsReady() != 0) {
        for (slot = 0; slot < D_80146327.count; slot++) {
            item = *(u16*)&D_80146327.items[slot * 2];
            Item_Add(item >> 8, item & BYTE_MASK, D_80146327.levels[slot], 0);
        }

        g_BattleStep    = 4;
        g_BattleSubStep = 0;
        g_BattleUIStep  = 0;
        g_BattleUIState = 0;
    }
}
