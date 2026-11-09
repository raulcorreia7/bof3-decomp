#include "engine/slus/slus.h"

/* latches two record fields into the bundle header color_1A pair, picking the word or halfword fields by the D_8014933C mode byte. */
MATCH void func_801583BC(void* obj) {
    s32 first;
    /* FAKE: pin the second field result in the retail destination register. Natural u16/s32 locals without the pin
       tried: 2 of 2 differ. */
    FAKE_REG(s32, second, "v1");

    if (D_8014933C != 0) {
        first  = *(u16*)((u8*)obj + 6);
        second = *(u16*)((u8*)obj + 10);
    } else {
        first  = *(s32*)((u8*)obj + 4);
        second = *(s32*)((u8*)obj + 8);
    }
    g_AreaMapBundle.color_1A[0] = first;
    g_AreaMapBundle.color_1A[1] = second;
}
