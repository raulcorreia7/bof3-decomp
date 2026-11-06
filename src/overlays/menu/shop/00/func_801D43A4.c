#include "shop_00.h"

MATCH void func_801D43A4(void) {
    u8 count;

    func_801D6E94();
    SND_StartXAStream(0, 1);
    count      = D_80148652;
    D_80148654 = 0x96;
    D_80148652 = count + 1;
}
