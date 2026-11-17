#include "battle_03.h"

/* func_801E6088 */
MATCH void Battle_HoldDamageNumber(void) {
    if (D_801EC2E0->arg.unk_09-- == 0) {
        D_801EC2E0->header.mode++;
        D_801EC2E0->arg.unk_09 = 4;
    }
}
