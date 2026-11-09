#include "plp278_00.h"

extern u8 D_80143FFC[];
extern u8 D_80144000[];
extern u8 D_80144006[];

MATCH s32 func_801CEA10(s32 arg0) {
    register s32 s0 asm("$16") = 1;
    register s32 s2 asm("$18");
    register s32 s1 asm("$17");
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");
    
    v0 = g_PartySize;
    if (s0 >= v0) {
        goto L801CEAC0;
    }
    v1 = arg0 & 0xFF;
    v0 = v1 << 3;
    v0 = v0 - v1;
    v0 = v0 << 2;
    v0 = v0 + v1;
    s2 = v0 << 2;
    s1 = 0x140;
L801CEA54:
    v0 = func_801BDD58(*(s32 *)(D_80143FFC + s2), 
                       *(s32 *)(D_80144000 + s2), 
                       (*(s16 *)(D_80144006 + s2)) + 0x200, 
                       1, (Actor *)((u8 *)&g_Game + s1));
    if (!(v0 & 0xFF)) {
        v0 = g_PartySize;
        s0 = s0 + 1;
        if (s0 < v0) {
            s1 = s1 + 0x140;
            goto L801CEA54;
        }
        goto L801CEAC0;
    }
    v0 = 1;
L801CEAC4:
    return v0;
L801CEAC0:
    v0 = 0;
    goto L801CEAC4;
}
