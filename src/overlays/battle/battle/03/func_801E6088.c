#include "battle_03.h"

MATCH void func_801E6088(void) {
    if (D_801EC2E0->unk_09-- == 0) {
        D_801EC2E0->header.mode++;
        D_801EC2E0->unk_09 = 4;
    }
}
