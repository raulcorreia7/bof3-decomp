#include "shop_00.h"

MATCH void func_801E2084(void) {
    u8 count;

    func_801E2650();
    count      = D_80148652;
    D_80148654 = 6;
    D_80148652 = count + 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
}
