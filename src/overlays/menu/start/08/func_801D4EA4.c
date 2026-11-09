#include "start_08.h"

/* Armor id list; the quantity list INV_ARMOR_QTY (0x8014534C) sits 0x200 bytes
 * on, and retail reaches it from this single base, so it stays an offset. */

MATCH void func_801D4EA4(void) {
    u8* ids;
    u8* qtys;
    u8  i;
    u8  j;
    u8  cur;
    u8  nxt;

    func_801D4A44();
    for (i = 0; i < INV_SLOTS_PER_CATEGORY - 1; i++) {
        ids  = g_InventoryIds[2];
        qtys = ids + 0x200;
        for (j = 0; j < INV_SLOTS_PER_CATEGORY - 1 - i; j++) {
            cur = *ids;
            if (cur != 0) {
                nxt = *(ids + 1);
                if ((nxt != 0) && (g_Armors[cur].power < g_Armors[nxt].power)) {
                    Menu_SwapBytes(ids, ids + 1);
                    Menu_SwapBytes(qtys, qtys + 1);
                }
            }
            ids++;
            qtys++;
        }
    }
}
