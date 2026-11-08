#include "battle_15.h"

MATCH bool func_800A82A0(u8 selection_id) {
    u8 count;
    u8 index;

    count = g_Battle.gene_count;
    index = 0;
    if (count != 0) {
        do {
            if (g_Battle.genes[index] == selection_id) {
                return true;
            }
            index++;
        } while (index < count);
    }
    return false;
}
