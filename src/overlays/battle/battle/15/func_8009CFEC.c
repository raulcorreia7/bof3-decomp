#include "battle_15.h"

MATCH void func_8009CFEC(void) {
    PanelOwner entries[8];
    u8         count;
    u8         i;
    u8         j;
    u8         found;

    count = 0;
    found = 0;
    for (i = 0; (u32)i < D_801EB5A8; i++) {
        for (j = 0; (u32)j < (u32)count; j++) {
            if (D_801EB630[D_801ED9B0[(u32)i].owner_index].enemy_id.byte.kind !=
                D_801EB630[entries[(u32)j].owner_index].enemy_id.byte.kind) {
                continue;
            }
            if (D_801ED9B0[(u32)i].panel_id != entries[(u32)j].panel_id) {
                continue;
            }
            found = 1;
            break;
        }
        if (!found) {
            entries[(u32)count] = D_801ED9B0[(u32)i];
            count++;
        }
        found = 0;
    }
    D_801EB5A8 = count;
    for (i = 0; (u32)i < D_801EB5A8; i++) {
        D_801ED9B0[(u32)i] = entries[(u32)i];
    }
}
