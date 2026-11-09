#include "shop_00.h"

/* File-local declarations: shop panel slot flags, kind/count/source bytes and frame halfwords are not declared by this target's shop_00.h. */

MATCH void func_801E2724(void) {
    u8* flags = D_80148378;

    D_80148379 = 7;
    D_8014837A = 0x10;
    D_8014837B = 2;
    D_8014837C = BATTLE_PARTY_STRIDE;
    D_8014837E = 0x3F;
    D_80148382 = D_80148361;
    *flags     = 1;
    D_8014839E = 0x11;
    D_801483A0 = 0xB4;
    D_8014839D = 7;
    D_8014839F = 2;
    D_801483A2 = 0xF0;
    flags += 0x24;
    *flags = 1;
}
