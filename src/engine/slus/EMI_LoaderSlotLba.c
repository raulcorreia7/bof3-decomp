#include "engine/slus/slus.h"

/* returns one loader slot's disc start LBA from the file table.
 */
MATCH DiscLba EMI_LoaderSlotLba(EmiSlotId slot_id) {
    return g_EmiSlotLbas[slot_id];
}
