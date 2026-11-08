#include "battle_15.h"

MATCH u8 func_800A6D84(void) {
    u8 index;

    for (index = 0; index < g_Battle.gene_count; index++) {
        if ((g_Battle.genes[index] == GENE_FUSION) && (g_Battle.living_party_count == 3)) {
            return func_800A805C();
        }
    }
    return 0;
}
