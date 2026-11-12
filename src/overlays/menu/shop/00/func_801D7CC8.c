#include "shop_00.h"

MATCH void func_801D7CC8(void) {
    volatile u8* slot;
    u8           count;

    slot = &D_80148656;
    func_801D7E1C(*slot, 152, 63, 0, 0xFF);
    func_801D8050(0);
    if ((func_801D81B4((u8*)(slot + 5), 16) & BYTE_MASK) != 0) {
        count      = D_80148651;
        D_80148654 = 0;
        D_80148651 = count - 2;
    }
}
