#include "engine/slus/slus.h"

/* returns one loader slot's disc start LBA from the file table.
 */
MATCH DiscLba EMI_GetArchiveSector(EMISlotId emi_id) {
    return g_EmiSlotLbas[emi_id];
}
